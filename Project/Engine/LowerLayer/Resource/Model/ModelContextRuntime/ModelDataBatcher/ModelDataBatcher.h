#pragma once
#include "../../ModelContext.h"

//外部
#include "../../../../../../Assets/Shared/ConstantBuffers.h"
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
//効率化のため
#include "../../../../Buffer/BufferContext.h"

class Model;

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
	//バッファに書き込まなくていいモデルも多数あるはずなので、全バッチングではなく、該当バッチングする
	void BatchAndUpdateModelData
	(
		AgentKey agentKey_,
		UINT const frameIndex_,
		std::vector<Model*>& models_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	//モデルの個体ごとに所持するパラメーター(TransformやMaterialなど)の配列のBufferIDのライブラリ
	std::unique_ptr<PerDrawBufferLibrary> perDrawBufferLibrary;

	//モデルのマテリアル情報、またはトランスフォームを書き込む
	///結合度に箔がついちゃうけど、さすがにモデルひとつごとにBufferDispatcherを解凍するのは非効率的すぎるし、
	///関数にまとめたいので
	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	void UpdateAndOverrideBuffer
	(
		UINT const frameIndex_,
		Model& model_,
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
		size_t const numMesh_,
		BufferContext::BufferDispatcher& dispatcher_
	);

};


struct ModelContext::ModelDataBatcher::Local_InputBufferUniqueIDLicence
{
private:

	friend class ModelDataCreator;
	explicit Local_InputBufferUniqueIDLicence() = default;
};

template<>
void ModelContext::ModelDataBatcher::UpdateAndOverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
(
	UINT const frameIndex_,
	Model& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	BufferContext::BufferDispatcher& dispatcher_
);

template<>
void ModelContext::ModelDataBatcher::UpdateAndOverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
(
	UINT const frameIndex_,
	Model& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	BufferContext::BufferDispatcher& dispatcher_
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

