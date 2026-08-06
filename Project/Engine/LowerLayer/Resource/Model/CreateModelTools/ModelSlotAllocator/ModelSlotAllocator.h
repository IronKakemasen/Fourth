#pragma once
#include"../../ModelContext.h"



class ModelContext::ModelSlotAllocator
{
	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	class MeshDataIDLibrary;


public:

	//TransformMatrixContainerBufferのスロットの割り当てを行う
	class TransformMatrixSlot;

	struct HandleLicence;
	struct AllocateLicence;

	ModelSlotAllocator(NexusFieldProof proof_);
	~ModelSlotAllocator();

	//空きスロットを分配する
	template<typename SlotType>
	uint32_t AllocateSlot(AllocateLicence licence_);

	MeshDataIDLibrary& AccessMeshDataIDLibrary(HandleLicence licence_);

private:

	std::unique_ptr<MeshDataIDLibrary> meshDataIDLibrary;
	std::unique_ptr<TransformMatrixSlot> transformMatrixSlot;

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
