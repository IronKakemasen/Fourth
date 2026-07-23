#pragma once
#include "../ModelDataCreator/ModelDataCreator.h"
#include "SimpleFreeList/SimpleFreeList.h"


struct ModelDataAggregate;

class MeshContext::ModelSlotAllocator
{
public:

	enum class SlotType
	{
		kTransformMatrix,

	};

	struct DistributeLicence;
	struct CreateModelDataLicence;


	template<SlotType slotType>
	uint32_t DistributeSlot(DistributeLicence licence_);

	//meshDataSRVHeapIndexGroupArraySRVHeapIndexこれを設定する
	void SetMeshDataSRVHeapIndexGroupArraySRVHeapIndex(std::unique_ptr<SRVHeapIndex>&& index_);

	//メッシュファイル名に対してMeshDataIDを紐づける
	void LinkModelFileNameToMeshDataID
	(
		CreateModelDataLicence licence_,
		std::string modelFileName_ , 
		const std::vector<MeshDataID>& idContainer_
	);

	ModelSlotAllocator(NexusFieldProof proof_);
	~ModelSlotAllocator();

private:

	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列のSRVHeapIndex
	std::unique_ptr<SRVHeapIndex> meshDataSRVHeapIndexGroupArraySRVHeapIndex;
	
	///「transformMatrixバッファ」の配列のSRVHeapIndex
	std::unique_ptr<SRVHeapIndex> transformMatrixBufferArraySRVHeapIndex;

	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	std::unordered_map<std::string, std::vector<MeshDataID>> meshDataIDLib;


	//TransformMatrixの空きインデックスのリスト
	SimpleFreeList transformMatrixSlotList;

};


struct MeshContext::ModelSlotAllocator::DistributeLicence
{
private:


	explicit DistributeLicence() = default;
};


struct MeshContext::ModelSlotAllocator::CreateModelDataLicence
{
private:

	friend class ModelDataCreator::MeshDataBufferCreator;
	explicit CreateModelDataLicence() = default;
};

