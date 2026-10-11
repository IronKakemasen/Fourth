#include "PreCompileHeader.h"
#include "ScenePipeline.h"
#include "SceneController/SceneController.h"
#include "SceneDataBatchingPlace/SceneDataBatchingPlace.h"

namespace
{
	auto const fileName = "ScenePipeline.cpp";
}


SceneContext::ScenePipeline::ScenePipeline(NexusFieldProof proof_, SceneLibrary& sceneLibrary_)
{
	sceneController = std::make_unique<SceneController>(proof_, sceneLibrary_);
	Logger::Log("Instantiate: SceneController", fileName);

}

SceneContext::ScenePipeline::~ScenePipeline()
{

}

void SceneContext::ScenePipeline::Run
(
	NexusFieldProof proof_,
	AgentKey key_,
	UINT const frameIndex_,
	ModelContextDiplomat& modelContextDiplomat_,
	CameraContextDiplomat& cameraContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//シーンの制御、更新処理
	sceneController->Run();
	
	//シーンで使用したデータのバッチング
	SceneDataBatchingPlace sceneDataBatchingPlace;
	sceneDataBatchingPlace.BatchingPlace
	(
		frameIndex_ ,
		*sceneController, 
		modelContextDiplomat_, 
		cameraContextDiplomat_,
		bufferContextDiplomat_
	);
}

