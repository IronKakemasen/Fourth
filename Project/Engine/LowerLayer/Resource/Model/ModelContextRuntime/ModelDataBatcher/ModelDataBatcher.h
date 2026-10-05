#pragma once
#include "../../ModelContext.h"


//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/ConstantBuffers.h"


class ModelContext::ModelDataBatcher
{
	//モデルの個体ごとに所持するTrnsformやMaterialなどのパラメーターの配列
	//のバッファのIDを格納している
	class PerDrawBufferLibrary;

public:

	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	struct BufferTypeTraits;

	struct Local_InputBufferUniqueIDLicence;

	ModelDataBatcher(NexusFieldProof proof_);
	~ModelDataBatcher();

	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	void ImportPerDrawBufferID(Local_InputBufferUniqueIDLicence licence_,BufferUniqueID id_);

	//代行者にランタイムでモデルデータのバッチング処理をやってもらう
	void BatchingAllModelData(NexusFieldProof proof_, AgentKey agentKey_);

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
	<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
{
	static inline std::string const kBufferName = "TransformMatrixContainer";
	static constexpr UINT kArrSize = (UINT)ProjectConfig::Render::CBufferSize::kSizeOfTransformMatrixContainerBuffer;
	static constexpr UINT kStructureSize = (UINT)sizeof(StructuredBufferModelData::TransformMatrixCPUGPU);
};

template<>
struct ModelContext::ModelDataBatcher::BufferTypeTraits
	<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
{
	static inline std::string const kBufferName = "MaterialContainer";
	static constexpr UINT kArrSize = (UINT)ProjectConfig::Render::CBufferSize::kSizeOfMaterialContainerBuffer;
	static constexpr UINT kStructureSize = (UINT)sizeof(StructuredBufferModelData::MaterialGPU);
};

