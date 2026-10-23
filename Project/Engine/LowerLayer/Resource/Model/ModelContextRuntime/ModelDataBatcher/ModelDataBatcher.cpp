#include "PreCompileHeader.h"
#include "ModelDataBatcher.h"
#include "PerDrawBufferLibrary/PerDrawBufferLibrary.h"
#include "../../ModelStructure/Model.h"


//外部
#include "../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include "../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"

using namespace ConstantBuffers;
using namespace StructuredBufferModelData;

ModelContext::ModelDataBatcher::ModelDataBatcher(NexusFieldProof proof_)
{
	perDrawBufferLibrary = std::make_unique<PerDrawBufferLibrary>(proof_);
}

ModelContext::ModelDataBatcher::~ModelDataBatcher()
{

}

void ModelContext::ModelDataBatcher::BatchModelData
(
	AgentKey agentKey_,
	UINT const frameIndex_,
	std::vector<Model*> const& models_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//BufferDispatcherを借りる
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence;
	auto& dispatcher = *bufferContextDiplomat_.Access<BufferContext::ToolLender>()->Lend<BufferContext::BufferDispatcher>(licence);

	//トランスフォームの書き込み先バッファ
	BufferUniqueID transformContainerBufferID = perDrawBufferLibrary->Export<ConstantBufferBindSlots::kTransformMatrixContainer>();
	auto dstWriteBufferTransform = static_cast<IWritableCPU*>(static_cast<UploadStructuredBuffer*>(dispatcher.Dispatch(transformContainerBufferID)));

	//マテリアルの書き込み先バッファ
	BufferUniqueID materialContainerBufferID = perDrawBufferLibrary->Export<ConstantBufferBindSlots::kMaterialContainer>();
	auto dstWriteBufferMaterial = static_cast<IWritableCPU*>(static_cast<UploadStructuredBuffer*>(dispatcher.Dispatch(materialContainerBufferID)));

	//モデルの所持するデータをバッファに書き込んでいく
	for (Model* model : models_)
	{
		auto const& perDrawIndices = model->WatchPerDrawIndices();
		auto const numMeshes = perDrawIndices.size();

		OverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
		(
			frameIndex_,
			*model,
			perDrawIndices,
			numMeshes,
			dstWriteBufferTransform
		);

		OverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
		(
			frameIndex_,
			*model,
			perDrawIndices,
			numMeshes,
			dstWriteBufferMaterial
		);
	}
}


template<>
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBufferBindSlots::kTransformMatrixContainer>
(
	UINT const frameIndex_,
	Model& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	IWritableCPU* writeDstBufferPtr_
)
{
	//書き込み用のダーティ判定しながら、該当インデックス(perDrawIndices)を辿って、バッファに書き込む
	//もちろんサブメッシュ分も
	for (size_t i = 0;i < numMesh_;++i)
	{
		auto& srcTransform = model_.RefTransform(i);
		
		//トランスフォームの更新用ダーティ判定をリセット
		srcTransform.ResetFrameFlag();

		//そのトランスフォームのデータを書き込む必要があるかどうか
		if (!srcTransform.ShouldOverrideBuffer()) continue;

		TransformMatrixCPUGPU transformMatrix(srcTransform.WatchWorldMatrix());
		writeDstBufferPtr_->WriteElement(frameIndex_, transformMatrix, perDrawIndices_[i].transformMatrixID);

		//トランスフォームのバッファ書き込みカウントを１つ減らす
		srcTransform.DecrementNeedOverrideBufferCnt();
	}

}

template<>
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBufferBindSlots::kMaterialContainer>
(
	UINT const frameIndex_,
	Model& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	IWritableCPU* writeDstBufferPtr_
)
{
	//やってることはトランスフォームとほぼ変わらない。
	for (size_t i = 0;i < numMesh_;++i)
	{
		//そのマテリアルがダーティじゃないなら書き込まない
		if (!model_.IsMaterialDirty(i)) continue;

		auto& srcMaterial = model_.WatchMaterial(i);
		//MaterialGPUに変換
		MaterialGPU material(srcMaterial);

		writeDstBufferPtr_->WriteElement(frameIndex_, material, perDrawIndices_[i].materialID);

		//マテリアルダーティのカウントを１つ消去
		model_.DecrementMaterialDirtyCnt(i);
	}
}


template<ConstantBufferBindSlots bindSlot>
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<bindSlot>(id_);
}


template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBufferBindSlots::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);

template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBufferBindSlots::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);
