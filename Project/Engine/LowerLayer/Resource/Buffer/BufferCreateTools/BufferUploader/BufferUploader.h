#pragma once
#include "../../BufferContext.h"

//外部
#include "../../../../Core/Command/ResourceUploader/ResourceUploader.h"


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
		UINT const resourceSize = sizeof(RealDataType) * numDataContaines_;

		//中間リソース生成
		ID3D12Resource* interMediateResource = CreateInterMediateResource(resourceSize);
		//サブリソース生成
		D3D12_SUBRESOURCE_DATA subResource = CreateBufferSubResource(realData_, resourceSize);
		
		//バッファと生リソースを取り出す
		auto [dstBuffer, dstResource,bufferName] = PickBufferAndResource(id_);

		//コピーしてアップロードする
		uploadCommand(dstResource, interMediateResource, &subResource, 1);

		//GPUBufferBehaviorから、IReadOnlyインターフェースにキャストしてバリアを抽出
		ExtractBarrier(dstBuffer);

		Logger::Log("Complete Uploading: " + bufferName + "(" + std::to_string(resourceSize) + ")", "BufferUploader.h");
	}

	//たまりにたまったバリアを張る
	//Nexusフィールド限定、代行者限定
	void PitchAllBarrier(BufferContext::NexusFieldProof proof_, BufferContext::AgentKey agentKey_);


private:

	//中間リソース生成
	class IntermediateResourceCreator;
	//BufferDispatcherを使って、バッファのユニークIDからバッファとその生リソースを取り出す
	class BufferAndResourcePicker;
	//コピーからシェーダーリソースに遷移するためのバリアを抽出
	class BarrierExtractor;

	BufferContext::ResourceCreator* resourceCreator;
	BufferContext::BufferDispatcher* dispatcher;
	//リソースをアップロードするコマンド
	CommandContext::ResourceUploader::UploadCommand uploadCommand;
	//バリアを張るためのコマンド
	CommandContext::ResourceUploader::PitchBarrierCommand pitchBarriersCommand;

	//中間リソースのコンテナ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> intermediateResources;
	//バリアのコンテナ
	std::vector<D3D12_RESOURCE_BARRIER> barriers;

	ID3D12Resource* CreateInterMediateResource(UINT const resourceSize_);
	void ExtractBarrier(GPUBufferBehavior* dstBuffer_);
	std::tuple<GPUBufferBehavior*, ID3D12Resource*,std::string> PickBufferAndResource(BufferUniqueID id_);

	template<typename RealDataType>
	D3D12_SUBRESOURCE_DATA CreateBufferSubResource(RealDataType* realData_ , UINT const resourceSize_)
	{
		D3D12_SUBRESOURCE_DATA subResource{};

		subResource.pData = realData_;
		subResource.RowPitch = resourceSize_;
		subResource.SlicePitch = subResource.RowPitch;

		return subResource;
	}
};

