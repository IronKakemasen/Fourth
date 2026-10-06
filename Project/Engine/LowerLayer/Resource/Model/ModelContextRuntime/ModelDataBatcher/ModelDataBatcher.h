#pragma once
#include "../../ModelContext.h"
#include "../../ModelStructure/Model.h"

//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/ConstantBuffers.h"

//効率化のため
#include "../../../../Buffer/BufferContext.h"

class ModelContext::ModelDataBatcher
{
	//モデルの個体ごとに所持するTrnsformやMaterialなどのパラメーターの配列
	//のバッファのIDを格納している
	class PerDrawBufferLibrary;

public:

	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	struct BufferTypeTraits;

	struct Local_InputBufferUniqueIDLicence;

	ModelDataBatcher
	(
		NexusFieldProof proof_,
		ModelContainer const& modelContainer_
	);
	~ModelDataBatcher();

	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	void ImportPerDrawBufferID(Local_InputBufferUniqueIDLicence licence_,BufferUniqueID id_);

	//代行者にランタイムでモデルデータのバッチング処理をやってもらう
	//staticかDynamicか選択
	template<Model::Type modelType>
	void BatchModelData
	(
		NexusFieldProof proof_,
		AgentKey agentKey_,
		BufferContextDiplomat& bufferContextDiplomat_,
		UINT const frameIndex_
	)
	{
		//BufferDispatcherを借りる
		auto& dispatcher = BorrowBufferDispatcher(bufferContextDiplomat_);

		//モデルタイプ別に仕分けされたコンテナ
		auto const& separatedContainer = PullModelContainer<modelType>(proof_);

		//モデルの所持するデータをバッファに書き込んでいく
		for (auto const& model : separatedContainer)
		{
			auto const& perDrawIndices = model->WatchPerDrawIndices();
			auto const numMaterials = perDrawIndices.size();

			OverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kTransformMatrixContainer>
			(
				frameIndex_,
				*model,
				perDrawIndices,
				numMaterials,
				dispatcher
			);

			OverrideBuffer<ConstantBuffers::ConstantBufferBindSlots::kMaterialContainer>
			(
				frameIndex_,
				*model,
				perDrawIndices,
				numMaterials,
				dispatcher
			);
		}
	}

private:

	//モデルの個体ごとに所持するパラメーター(TransformやMaterialなど)の配列のBufferIDのライブラリ
	std::unique_ptr<PerDrawBufferLibrary> perDrawBufferLibrary;
	ModelContainer const& modelContainer;

	//モデルのマテリアル情報、またはトランスフォームを書き込む
	///結合度に箔がついちゃうけど、さすがにモデルひとつごとにBufferDispatcherを解凍するのは非効率的すぎるし、
	///関数にまとめたいので
	template<ConstantBuffers::ConstantBufferBindSlots bufferType>
	void OverrideBuffer
	(
		UINT const frameIndex_,
		Model const& model_,
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
		size_t const numMesh_,
		BufferContext::BufferDispatcher& dispatcher_
	);

	//BufferDispatcherを借りる
	BufferContext::BufferDispatcher& BorrowBufferDispatcher(BufferContextDiplomat& bufferContextDiplomat_);

	//モデルコンテナクラスから、仕分け済みのモデルコンテナを引っ張る
	template<Model::Type modelType>
	std::vector<Model*> const& PullModelContainer(NexusFieldProof proof_);
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

