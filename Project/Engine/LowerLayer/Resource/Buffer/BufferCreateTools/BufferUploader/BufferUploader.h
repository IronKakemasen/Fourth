#pragma once
#include "../../BufferContext.h"

//外部
#include "../../../../Core/Command/ResourceUploader/ResourceUploader.h"


class GPUBufferBehavior;

class BufferContext::BufferUploader
{
	//一時的にアップロードするバッファの情報を保持するための形式
	struct TemporaryBufferInfoStorage
	{
		BufferUniqueID id;
		ID3D12Resource* intermediateResource;
		D3D12_SUBRESOURCE_DATA subResource;
		UINT resourceSize;
		std::vector<std::byte> ownedData;
	};


public:

	BufferUploader
	(
		BufferContext::NexusFieldProof proof_,
		BufferContext::ResourceCreator* resourceCreator_,
		BufferContext::BufferDispatcher* dispatcher_,
		CommandContextDiplomat* commandContextDiplomat_
	);

	~BufferUploader();

	///アップロードするバッファの必要情報の登録
	template<typename RealDataType>
	void RegisterBuffer
	(
		const BufferUniqueID id_,
		const UINT numDataContaines_,
		const RealDataType* realData_
	)
	{
		TemporaryBufferInfoStorage temporaryBufferInfoStorage;
		UINT const resourceSize = sizeof(RealDataType) * numDataContaines_;

		temporaryBufferInfoStorage.id = id_;
		temporaryBufferInfoStorage.resourceSize = resourceSize;
		temporaryBufferInfoStorage.intermediateResource = CreateInterMediateResource(resourceSize);
		temporaryBufferInfoStorage.subResource = CreateBufferSubResource(realData_, resourceSize);

		//実データをコピーして自前で保持する
		temporaryBufferInfoStorage.ownedData.resize(resourceSize);
		memcpy(temporaryBufferInfoStorage.ownedData.data(), realData_, resourceSize);

		//subResource.pDataは、コピー先(ownedData)を指すようにする
		temporaryBufferInfoStorage.subResource = CreateBufferSubResource
		(
			reinterpret_cast<const RealDataType*>(temporaryBufferInfoStorage.ownedData.data()),
			resourceSize
		);

		temporaryBufferInfoStorageContainer.emplace_back(std::move(temporaryBufferInfoStorage));
	}


	///バッファをアップロードする(テクスチャバッファはまた別。あとで共通窓口を作る)
	///Nexusフィールド限定、代行者限定
	void UploadBuffer(BufferContext::NexusFieldProof proof_, BufferContext::AgentKey agentKey_);


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
	std::vector<TemporaryBufferInfoStorage> temporaryBufferInfoStorageContainer;


	//中間リソースの生成
	ID3D12Resource* CreateInterMediateResource(UINT const resourceSize_);
	
	//バリアを吐かせる
	template<D3D12_RESOURCE_STATES state>
	void ExtractBarrier(GPUBufferBehavior* dstBuffer_);

	//バッファと生ポインタのフェッチ
	std::tuple<GPUBufferBehavior*, ID3D12Resource*> PickBufferAndResource(BufferUniqueID id_)const;

	//コマンドを流す
	void Flush(std::string log_);

	//終わりの一言
	void EndLog()const;

	template<typename RealDataType>
	D3D12_SUBRESOURCE_DATA CreateBufferSubResource(RealDataType* realData_ , UINT const resourceSize_)const
	{
		D3D12_SUBRESOURCE_DATA subResource{};

		subResource.pData = realData_;
		subResource.RowPitch = resourceSize_;
		subResource.SlicePitch = subResource.RowPitch;

		return subResource;
	}
};

