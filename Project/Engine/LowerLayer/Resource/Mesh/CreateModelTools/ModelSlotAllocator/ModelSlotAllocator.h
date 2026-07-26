#pragma once
#include"../../MeshContext.h"
#include "SimpleFreeList/SimpleFreeList.h"


struct ModelDataAggregate;

class MeshContext::ModelSlotAllocator
{
	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	class MeshDataIDLibrary;

public:

	enum class SlotType
	{
		kTransformMatrix,

	};

	struct HandleLicence;
	struct AllocateLicence;

	//空きスロットを分配する
	template<SlotType slotType>
	uint32_t AllocateSlot(AllocateLicence licence_);

	//meshDataSRVHeapIndexGroupContainerのSRVHeapIndexセットする
	void SetMeshDataSRVHeapIndexGroupContainerSRVHeapIndex(HandleLicence licence_ , SRVHeapIndex index_);

	//meshDataIDLibraryにアクセスする
	MeshDataIDLibrary& AccessMeshDataIDLibrary(HandleLicence licence_);

	ModelSlotAllocator(NexusFieldProof proof_);
	~ModelSlotAllocator();

private:

	std::unique_ptr<MeshDataIDLibrary> meshDataIDLibrary;


	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列のSRVHeapIndex
	std::optional<SRVHeapIndex> meshDataSRVHeapIndexGroupContainerSRVHeapIndex;
	
	///「transformMatrixバッファ」の配列のSRVHeapIndex
	std::optional<SRVHeapIndex> transformMatrixBufferArraySRVHeapIndex;

	//TransformMatrixの空きインデックスのリスト
	SimpleFreeList transformMatrixSlotList;

};


struct MeshContext::ModelSlotAllocator::HandleLicence
{
private:

	friend class ModelDataCreator;
	friend class ModelAssembler;
	explicit HandleLicence() = default;
};

struct MeshContext::ModelSlotAllocator::AllocateLicence
{
private:

	friend class ModelAssembler;
	explicit AllocateLicence() = default;
};

