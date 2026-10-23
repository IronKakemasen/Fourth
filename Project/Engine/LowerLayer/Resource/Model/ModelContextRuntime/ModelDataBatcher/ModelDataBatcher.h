#pragma once
#include "../../ModelContext.h"

//外部
#include "../../../../../../Assets/Shared/ConstantBuffers.h"
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"

class Model;
struct IWritableCPU;

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
	void BatchModelData
	(
		AgentKey agentKey_,
		UINT const frameIndex_,
		std::vector<Model*> const& models_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	//モデルの個体ごとに所持するパラメーター(TransformやMaterialなど)の配列のBufferIDのライブラリ
	std::unique_ptr<PerDrawBufferLibrary> perDrawBufferLibrary;

	//モデルのマテリアル情報、またはトランスフォームを書き込む
	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	void OverrideBuffer
	(
		UINT const frameIndex_,
		Model& model_,
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
		size_t const numMesh_,
		IWritableCPU* writeDstBufferPtr_
	);

};


struct ModelContext::ModelDataBatcher::Local_InputBufferUniqueIDLicence
{
private:

	friend class ModelDataCreator;
	explicit Local_InputBufferUniqueIDLicence() = default;
};

template<>
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
(
	UINT const frameIndex_,
	Model& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	IWritableCPU* writeDstBufferPtr_
);

template<>
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
(
	UINT const frameIndex_,
	Model& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	IWritableCPU* writeDstBufferPtr_
);


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

