#include "PreCompileHeader.h"
#include "ModelDataBatcher.h"
#include "PerDrawBufferLibrary/PerDrawBufferLibrary.h"
#include "../../ModelContainer/ModelContainer.h"


//外部
#include "../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include "../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"

using namespace ConstantBuffers;
using namespace StructuredBufferModelData;

ModelContext::ModelDataBatcher::ModelDataBatcher
(
	NexusFieldProof proof_,
	ModelContainer const& modelContainer_
):modelContainer(modelContainer_)
{
	perDrawBufferLibrary = std::make_unique<PerDrawBufferLibrary>(proof_);

}

ModelContext::ModelDataBatcher::~ModelDataBatcher()
{

}

BufferContext::BufferDispatcher& ModelContext::ModelDataBatcher::BorrowBufferDispatcher(BufferContextDiplomat& bufferContextDiplomat_)
{
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence;

	return *bufferContextDiplomat_.Access<BufferContext::ToolLender>()->Lend<BufferContext::BufferDispatcher>(licence);
}

template<>
std::vector<Model*> const& ModelContext::ModelDataBatcher::PullModelContainer<Model::Type::kStatic>(NexusFieldProof proof_)
{
	return modelContainer.WatchSeparatedByModelType(proof_)[(UINT)Model::Type::kStatic];
}

template<>
std::vector<Model*> const& ModelContext::ModelDataBatcher::PullModelContainer<Model::Type::kDynamic>(NexusFieldProof proof_)
{
	return modelContainer.WatchSeparatedByModelType(proof_)[(UINT)Model::Type::kDynamic];
}


template<>
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBufferBindSlots::kTransformMatrixContainer>
(
	UINT const frameIndex_,
	Model const& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	BufferContext::BufferDispatcher& dispatcher_
)
{
	//書き込み先バッファ
	BufferUniqueID transformContainerBufferID = perDrawBufferLibrary->Export<ConstantBufferBindSlots::kTransformMatrixContainer>();
	auto dstBuffer = static_cast<IWritableCPU*>(static_cast<UploadStructuredBuffer*>(dispatcher_.Dispatch(transformContainerBufferID)));

	//ダーティ判定しながら、該当インデックス(perDrawIndices)を辿って、バッファに書き込む
	//もちろんサブメッシュ分も
	for (size_t i = 0;i < numMesh_;++i)
	{
		auto const& srcTransform = model_.WatchTransform(i);

		//そのトランスフォームがダーティなら書き込まない
		if (!srcTransform.ShouldOverrideBuffer()) continue;

		TransformMatrixCPUGPU transformMatrix(srcTransform.WatchWorldMatrix());
		dstBuffer->WriteElement(frameIndex_, transformMatrix, perDrawIndices_[i].transformMatrixID);
	}
}

template<>
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBufferBindSlots::kMaterialContainer>
(
	UINT const frameIndex_,
	Model const& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	BufferContext::BufferDispatcher& dispatcher_
)
{
	//書き込み先バッファ
	BufferUniqueID materialContainerBufferID = perDrawBufferLibrary->Export<ConstantBufferBindSlots::kMaterialContainer>();
	auto dstBuffer = static_cast<IWritableCPU*>(static_cast<UploadStructuredBuffer*>(dispatcher_.Dispatch(materialContainerBufferID)));

	//やってることはトランスフォームと変わらない。
	for (size_t i = 0;i < numMesh_;++i)
	{
		//そのトランスフォームがダーティなら書き込まない
		if (!model_.IsMaterialDirty(i)) continue;

		const auto& srcMaterial = model_.WatchMaterial(i);
		MaterialGPU material(srcMaterial);

		dstBuffer->WriteElement(frameIndex_, material, perDrawIndices_[i].materialID);
	}
}




template
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBufferBindSlots::kTransformMatrixContainer>
(
	UINT const frameIndex_,
	Model const& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	BufferContext::BufferDispatcher& dispatcher_
);
template
void ModelContext::ModelDataBatcher::OverrideBuffer<ConstantBufferBindSlots::kMaterialContainer>
(
	UINT const frameIndex_,
	Model const& model_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	size_t const numMesh_,
	BufferContext::BufferDispatcher& dispatcher_
);


template
std::vector<Model*> const& ModelContext::ModelDataBatcher::PullModelContainer<Model::Type::kStatic>(NexusFieldProof proof_);
template
std::vector<Model*> const& ModelContext::ModelDataBatcher::PullModelContainer<Model::Type::kDynamic>(NexusFieldProof proof_);



template<>
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBufferBindSlots::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<ConstantBufferBindSlots::kTransformMatrixContainer>(id_);
}

template<>
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBufferBindSlots::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_)
{
	perDrawBufferLibrary->Import<ConstantBufferBindSlots::kMaterialContainer>(id_);
}


template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBufferBindSlots::kTransformMatrixContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);

template
void ModelContext::ModelDataBatcher::ImportPerDrawBufferID<ConstantBufferBindSlots::kMaterialContainer>
(Local_InputBufferUniqueIDLicence licence_, BufferUniqueID id_);
