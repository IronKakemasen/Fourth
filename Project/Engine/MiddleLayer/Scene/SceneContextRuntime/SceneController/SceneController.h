#pragma once
#include "../ScenePipeline.h"
#include "../../SceneStructure/SceneBehavior.h"

class SceneContext::ScenePipeline::SceneController
{
public:

	SceneController
	(
		NexusFieldProof proof_,
		SceneLibrary& sceneLib_
	);

	//シーンの制御、更新処理
	void Run();


	SceneBehavior::Output const& WatchCurrentSceneOutput()const;

private:

	void ChangeScene(std::string const& next_);


	//現在稼働しているシーン
	SceneBehavior* curScene = nullptr;
	SceneLibrary& sceneLib;
};

