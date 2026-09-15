#pragma once
#include "../../ModelContext.h"


//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/ConstantBuffers.h"


class ModelContext::ModelDataBatcher
{
	class PerDrawBufferLibrary;

public:

	struct Local_InputBufferUniqueIDLicence;

	enum class BufferType
	{
		kTransformMatrixContainer,
		kMaterialContainer
		

		,kCount
	};

	ModelDataBatcher(NexusFieldProof proof_);
	~ModelDataBatcher();

	template<BufferType idType>
	void ImportPerDrawBufferID(Local_InputBufferUniqueIDLicence licence_,BufferUniqueID id_);

	template<BufferType idType>
	struct BufferTypeTraits;

private:

	std::unique_ptr<PerDrawBufferLibrary> perDrawBufferLibrary;

};


struct ModelContext::ModelDataBatcher::Local_InputBufferUniqueIDLicence
{
private:

	friend class ModelDataCreator;
	explicit Local_InputBufferUniqueIDLicence() = default;
};


template<>
struct ModelContext::ModelDataBatcher::BufferTypeTraits
	<ModelContext::ModelDataBatcher::BufferType::kTransformMatrixContainer>
{
	static inline std::string const kBufferName = "TransformMatrixContainer";
	static constexpr UINT kArrSize = (UINT)ProjectConfig::Render::CBufferSize::kSizeOfTransformMatrixContainerBuffer;
	static constexpr UINT kStructureSize = (UINT)sizeof(StructuredBufferModelData::TransformMatrixCPUGPU);
	//static constexpr UINT kConstantBufferSlot = (UINT)ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer;
};

template<>
struct ModelContext::ModelDataBatcher::BufferTypeTraits
	<ModelContext::ModelDataBatcher::BufferType::kMaterialContainer>
{
	static inline std::string const kBufferName = "MaterialContainer";
	static constexpr UINT kArrSize = (UINT)ProjectConfig::Render::CBufferSize::kSizeOfMaterialContainerBuffer;
	static constexpr UINT kStructureSize = (UINT)sizeof(StructuredBufferModelData::MaterialGPU);
	//static constexpr UINT kConstantBufferSlot = (UINT)ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer;

};

