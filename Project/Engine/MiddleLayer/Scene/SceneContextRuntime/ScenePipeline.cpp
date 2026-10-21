#include "PreCompileHeader.h"
#include "ScenePipeline.h"
#include "SceneController/SceneController.h"
#include "SceneDataBatchingPlace/SceneDataBatchingPlace.h"
#include "../SceneLibrary/SceneLibrary.h"

namespace
{
	auto const fileName = "ScenePipeline.cpp";
}


SceneContext::ScenePipeline::ScenePipeline(NexusFieldProof proof_)
{
	sceneLibrary = std::make_unique<SceneLibrary>(proof_);
	Logger::Log("Instantiate: SceneLibrary", fileName);

	sceneController = std::make_unique<SceneController>(proof_, *sceneLibrary);
	Logger::Log("Instantiate: SceneController", fileName);

}

SceneContext::ScenePipeline::~ScenePipeline()
{

}


void SceneContext::ScenePipeline::ImportScene(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_)
{
	sceneLibrary->Import(std::move(scene_), sceneName_);

	//スタートアップシーンを設定
#ifdef _DEBUG

	if (sceneName_ == ProjectConfig::Window::FirstSceneDebug())
	{
		sceneController->ChangeScene(sceneName_);
	}

#endif // DEBUG

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

