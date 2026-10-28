#include "PreCompileHeader.h"
#include "SceneDataBatchingPlace.h"
#include "../SceneController/SceneController.h"
#include "../../SceneStructure/SceneOutput/SceneOutput.h"

//外部
#include "../../../../LowerLayer/Resource/Camera/CameraContextDiplomats.h"

#include "../../../../LowerLayer/Resource/Model/ModelContextDiplomatIncludes.h"
#include "../../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelContainer/ModelContainer.h"

using namespace ProjectConfig::Render;

void SceneContext::ScenePipeline::SceneDataBatchingPlace::BatchingPlace
(
	UINT const frameIndex_,
	SceneController const& sceneController_,
	ModelContextDiplomat& modelContextDiplomat_,
	CameraContextDiplomat& cameraContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	auto const& sceneOutput = sceneController_.WatchCurrentSceneOutput();

	//カメラコンテキストの代行者
	auto& cameraAgent = cameraContextDiplomat_.Access<CameraContext::ExecutionAgent>();
	//カメラデータのバッチング
	cameraAgent.BatchCameraData
	(
		CameraContext::ExecutionAgent::SceneContextProof{},
		sceneOutput.WatchUsingCamera(),
		frameIndex_,
		bufferContextDiplomat_
	);

	//モデルコンテキストの代行者
	auto& modelAgent = modelContextDiplomat_.Access<ModelContext::ExecutionAgent>();
	
	//モデルデータのバッチング
	modelAgent.BatchModelData
	(
		ModelContext::ExecutionAgent::SceneContextProof{},
		frameIndex_,
		sceneOutput.WatchModelContainer()->WatchSeparatedByModelType()[(UINT)Model::Type::kDynamic],
		bufferContextDiplomat_
	);

	if (sceneOutput.WatchLeftStaticModelBatchingCnt() <= (UINT)NumBuffer::kDoubleBuffer)
	{
		modelAgent.BatchModelData
		(
			ModelContext::ExecutionAgent::SceneContextProof{},
			frameIndex_,
			sceneOutput.WatchModelContainer()->WatchSeparatedByModelType()[(UINT)Model::Type::kStatic],
			bufferContextDiplomat_
		);
	}
}

