#pragma once
#include"../../ModelContext.h"



class ModelContext::ModelSlotAllocator
{
	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	class ModelDataLibrary;

public:

	//TransformMatrixContainerBufferのスロットの割り当てを行う
	class TransformMatrixSlot;
	//MaterialContainerBufferのスロット割り当てを行う
	class MaterialSlot;

	struct HandleLicence;
	struct AllocateLicence;

	ModelSlotAllocator(NexusFieldProof proof_);
	~ModelSlotAllocator();

	//空きスロットを分配する
	template<typename SlotType>
	uint32_t AllocateSlot(AllocateLicence licence_);

	ModelDataLibrary& AccessModelDataLibrary(HandleLicence licence_);

private:

	std::unique_ptr<ModelDataLibrary> modelDataLibrary;
	std::unique_ptr<TransformMatrixSlot> transformMatrixSlot;
	std::unique_ptr<MaterialSlot> materialSlot;

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

template<>
uint32_t ModelContext::ModelSlotAllocator::AllocateSlot
<ModelContext::ModelSlotAllocator::MaterialSlot>(AllocateLicence licence_);
