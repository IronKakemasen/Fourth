#pragma once
#include "../../MeshContext.h"
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
	struct ResizeLicence;


	template<SlotType slotType>
	uint32_t DistributeSlot(DistributeLicence licence_);

	//meshDataSRVHeapIndexGroupArraySRVHeapIndexこれを設定する
	void SetMeshDataSRVHeapIndexGroupArraySRVHeapIndex(std::unique_ptr<SRVHeapIndex>&& index_);

	ModelSlotAllocator(MeshContext::InstanceKey key_);
	~ModelSlotAllocator();

private:

	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列のSRVHeapIndex
	std::unique_ptr<SRVHeapIndex> meshDataSRVHeapIndexGroupArraySRVHeapIndex;
	///「transformMatrixバッファ」の配列のSRVHeapIndex
	std::unique_ptr<SRVHeapIndex> transformMatrixBufferArraySRVHeapIndex;


	//TransformMatrixの空きインデックスのリスト
	SimpleFreeList transformMatrixSlotList;

};


struct MeshContext::ModelSlotAllocator::DistributeLicence
{
private:


	explicit DistributeLicence() = default;
};




struct MeshContext::ModelSlotAllocator::ResizeLicence
{
private:

	friend class MeshContext::ModelDataCreator;
	explicit ResizeLicence() = default;
};

