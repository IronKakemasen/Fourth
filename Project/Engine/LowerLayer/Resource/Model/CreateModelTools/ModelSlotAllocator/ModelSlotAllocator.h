#pragma once
#include"../../ModelContext.h"


struct ModelDataAggregate;

class ModelContext::ModelSlotAllocator
{
	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	class MeshDataIDLibrary;


public:

	struct HandleLicence;
	struct AllocateLicence;

	//TransformMatrixContainerBufferのスロットの割り当てを行う
	class TransformMatrixSlot;

	//空きスロットを分配する
	template<typename SlotType>
	uint32_t AllocateSlot(AllocateLicence licence_);

	//meshDataSRVHeapIndexGroupContainerのSRVHeapIndexセットする
	void SetMeshDataSRVHeapIndexGroupContainerSRVHeapIndex(HandleLicence licence_ , SRVHeapIndex index_);

	//meshDataIDLibraryにアクセスする
	MeshDataIDLibrary& AccessMeshDataIDLibrary(HandleLicence licence_);

	ModelSlotAllocator(NexusFieldProof proof_);
	~ModelSlotAllocator();

private:

	std::unique_ptr<MeshDataIDLibrary> meshDataIDLibrary;
	std::unique_ptr<TransformMatrixSlot> transformMatrixSlot;

	
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列のSRVHeapIndex
	std::optional<SRVHeapIndex> meshDataSRVHeapIndexGroupContainerSRVHeapIndex;
	
	///「transformMatrixバッファ」の配列のSRVHeapIndex
	std::optional<SRVHeapIndex> transformMatrixBufferArraySRVHeapIndex;


};


struct ModelContext::ModelSlotAllocator::HandleLicence
{
private:

	friend class ModelDataCreator;
	friend class ModelDescAssembler;
	explicit HandleLicence() = default;
};

struct ModelContext::ModelSlotAllocator::AllocateLicence
{
private:

	friend class ModelDescAssembler;
	explicit AllocateLicence() = default;
};


template<>
uint32_t ModelContext::ModelSlotAllocator::AllocateSlot
<ModelContext::ModelSlotAllocator::TransformMatrixSlot>(AllocateLicence licence_);
