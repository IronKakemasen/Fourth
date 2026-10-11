#include "PreCompileHeader.h"
#include "SceneDataBatchingPlace.h"
#include "../SceneController/SceneController.h"

//外部
#include "../../../../LowerLayer/Resource/Camera/CameraContextDiplomats.h"


SceneContext::ScenePipeline::SceneDataBatchingPlace::SceneDataBatchingPlace()
{

}

void SceneContext::ScenePipeline::SceneDataBatchingPlace::BatchingPlace
(
	UINT const frameIndex_,
	SceneController const& sceneController_,
	ModelContextDiplomat& modelContextDiplomat_,
	CameraContextDiplomat& cameraContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	auto const& sceneOutput = sceneController_.WatchSceneOutput();

	//カメラコンテキストの代行者
	auto& cameraAgent = cameraContextDiplomat_.Access<CameraContext::ExecutionAgent>();
	//カメラデータのバッチング
	cameraAgent.BatchCameraData
	(
		CameraContext::ExecutionAgent::SceneContextProof{},
		sceneOutput.usingCamera,
		frameIndex_,
		bufferContextDiplomat_
	);


}
