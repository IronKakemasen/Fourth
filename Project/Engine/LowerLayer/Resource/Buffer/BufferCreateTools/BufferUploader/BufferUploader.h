#pragma once
#include "../../BufferContext.h"

#include "../../BufferDefinition/GPUBuffer/StaticStructuredBuffer/StaticStructuredBuffer.h"
#include "../../RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"

//外部
#include "../../../../Core/Command/CommandContext.h"


class GPUBufferBehavior;

class BufferContext::BufferUploader
{
public:

	BufferUploader
	(
		BufferContext::NexusFieldProof proof_,
		BufferContext::ResourceCreator* resourceCreator_,
		BufferContext::BufferDispatcher* dispatcher_,
		CommandContextDiplomat* commandContextDiplomat_
	);

	~BufferUploader();

	///バッファをアップロードする(テクスチャバッファはまた別。あとで共通窓口を作る)
	template<typename RealDataType>
	void UploadBuffer
	(
		const BufferUniqueID id_,
		const UINT numDataContaines_,
		const RealDataType* realData_
	)
	{
		UINT const bufferSize = sizeof(RealDataType) * numDataContaines_;

		//中間リソース生成
		ID3D12Resource* interMediateResource = CreateInterMediateResource(bufferSize);
		//サブリソース生成
		D3D12_SUBRESOURCE_DATA subResource = CreateBufferSubResource(realData_, bufferSize);
		
		//生リソースを取り出す
		GPUBufferBehavior* dstBuffer = dispatcher->Dispatch(id_);
		ID3D12Resource* dstResource = dstBuffer->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 0);

		//コピーしてアップロードする
		uploadCommand(dstResource, interMediateResource, &subResource, 1);

		//GPUBufferBehaviorから、IReadOnlyインターフェースにキャストしてバリアを張る
		IReadOnly* readOnlyBuffer = dynamic_cast<IReadOnly*>(dstBuffer);
		ErrorMessageOutput::Assert::DetectError(readOnlyBuffer, "リードオンリーなバッファじゃない", "BufferUploader.h");
		//コピーからシェーダーリソースに遷移させるバリアを吐かせる
		auto barrier_copyDstToShaderResource = readOnlyBuffer->CreateBarrierAsReading();
		barriers.emplace_back(barrier_copyDstToShaderResource);

		Logger::Log("Complete Uploading: " + dstBuffer->WatchName() + "(" + std::to_string(bufferSize) + ")", "BufferUploader.h");
	}

private:
	BufferContext::ResourceCreator* resourceCreator;
	BufferContext::BufferDispatcher* dispatcher;
	CommandContext::UploadCommand uploadCommand;

	//中間リソースのコンテナ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> intermediateResources;
	//バリアのコンテナ
	std::vector<D3D12_RESOURCE_BARRIER> barriers;


	D3D12_RESOURCE_DESC CreateIntermedeiteResourceDesc(UINT resourceSize_)const;
	D3D12_HEAP_PROPERTIES CreateIntermedeiteHeapProp()const;
	ID3D12Resource* CreateInterMediateResource(UINT resourceSize_);

	template<typename RealDataType>
	D3D12_SUBRESOURCE_DATA CreateBufferSubResource(RealDataType* realData_ , UINT const bufferSize_)
	{
		D3D12_SUBRESOURCE_DATA subResource{};

		subResource.pData = realData_;
		subResource.RowPitch = bufferSize_;
		subResource.SlicePitch = subResource.RowPitch;

		return subResource;
	}
};

