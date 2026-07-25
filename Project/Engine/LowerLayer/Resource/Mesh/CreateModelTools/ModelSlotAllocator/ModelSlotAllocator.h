#pragma once
#include"../../MeshContext.h"
#include "SimpleFreeList/SimpleFreeList.h"


struct ModelDataAggregate;

class MeshContext::ModelSlotAllocator
{
public:

	enum class SlotType
	{
		kTransformMatrix,

	};

	struct HandleLicence;


	//空きスロットを分配する
	template<SlotType slotType>
	uint32_t DistributeSlot(HandleLicence licence_);

	//meshDataSRVHeapIndexGroupContainerのSRVHeapIndexセットする
	void SetMeshDataSRVHeapIndexGroupContainerSRVHeapIndex(HandleLicence licence_ , std::unique_ptr<SRVHeapIndex>&& index_);

	//メッシュファイル名に対してMeshDataID(複数)を紐づける
	void LinkModelFileNameToMeshDataID
	(
		HandleLicence licence_,
		std::string modelFileName_ , 
		const std::vector<MeshDataID>& idContainer_
	);

	//内容をログファイルに書き出す
	void Log(HandleLicence licence_);

	ModelSlotAllocator(NexusFieldProof proof_);
	~ModelSlotAllocator();

private:

	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列のSRVHeapIndex
	std::unique_ptr<SRVHeapIndex> meshDataSRVHeapIndexGroupContainerSRVHeapIndex;
	
	///「transformMatrixバッファ」の配列のSRVHeapIndex
	std::unique_ptr<SRVHeapIndex> transformMatrixBufferArraySRVHeapIndex;

	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	std::unordered_map<std::string, std::vector<MeshDataID>> meshDataIDLib;


	//TransformMatrixの空きインデックスのリスト
	SimpleFreeList transformMatrixSlotList;

};


struct MeshContext::ModelSlotAllocator::HandleLicence
{
private:

	friend class ModelDataCreator;
	explicit HandleLicence() = default;
};

