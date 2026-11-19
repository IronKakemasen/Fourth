#include "PreCompileHeader.h"
#include "SceneDataBatchingPlace.h"
#include "../SceneController/SceneController.h"
#include "../../SceneStructure/SceneOutput/SceneOutput.h"

//外部
#include "../../../../LowerLayer/Resource/Camera/CameraContextDiplomats.h"

#include "../../../../LowerLayer/Resource/Model/ModelContextDiplomatIncludes.h"
#include "../../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelContainer/ModelContainer.h"

#include "../../../../LowerLayer/Resource/Material/MaterialContextDiplomats.h"

using namespace ProjectConfig::Render;

void SceneContext::ScenePipeline::SceneDataBatchingPlace::BatchingPlace
(
	UINT const frameIndex_,
	SceneController const& sceneController_,
	ModelContextDiplomat& modelContextDiplomat_,
	CameraContextDiplomat& cameraContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	MaterialContextDiplomat& materialContextDiplomat_
)
{
	auto const& sceneOutput = sceneController_.WatchCurrentSceneOutput();

	//モデルコンテキストの代行者
	auto& modelAgent = modelContextDiplomat_.Access<ModelContext::ExecutionAgent>();
	//カメラコンテキストの代行者
	auto& cameraAgent = cameraContextDiplomat_.Access<CameraContext::ExecutionAgent>();
	//マテリアルコンテキストの代行者
	auto& materialAgent = materialContextDiplomat_.Access<MaterialContext::ExecutionAgent>();

	//カメラデータのバッチング
	cameraAgent.BatchCameraData
	(
		CameraContext::ExecutionAgent::SceneContextProof{},
		sceneOutput.WatchUsingCamera(),
		frameIndex_,
		bufferContextDiplomat_
	);

	
	//モデルデータのバッチング
	modelAgent.BatchModelData
	(
		ModelContext::ExecutionAgent::SceneContextProof{},
		frameIndex_,
		sceneOutput.WatchModelContainer()->WatchSeparatedByModelType<Model::MeshUpdateType::kDynamic>(),
		bufferContextDiplomat_
	);

	//マテリアルデータのバッチング
	materialAgent.WriteInAllMaterialData
	(
		MaterialContext::ExecutionAgent::SceneContextProof{},
		sceneOutput.WatchCollectedMaterialBatchFormatsArr()[UINT(Materials::UpdateType::kDynamic)],
		frameIndex_,
		bufferContextDiplomat_
	);


	//Staticなものはここでまとめて
	if (sceneOutput.WatchLeftStaticBatchingCnt() <= (UINT)NumBuffer::kDoubleBuffer)
	{
		modelAgent.BatchModelData
		(
			ModelContext::ExecutionAgent::SceneContextProof{},
			frameIndex_,
			sceneOutput.WatchModelContainer()->WatchSeparatedByModelType<Model::MeshUpdateType::kStatic>(),
			bufferContextDiplomat_
		);

		materialAgent.WriteInAllMaterialData
		(
			MaterialContext::ExecutionAgent::SceneContextProof{},
			sceneOutput.WatchCollectedMaterialBatchFormatsArr()[UINT(Materials::UpdateType::kStatic)],
			frameIndex_,
			bufferContextDiplomat_
		);

	}
}

