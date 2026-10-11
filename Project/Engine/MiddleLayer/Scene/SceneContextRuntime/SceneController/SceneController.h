#pragma once
#include "../../SceneContext.h"
#include "../../SceneStructure/SceneBehavior.h"

class SceneContext::SceneController
{
public:

	SceneController
	(
		NexusFieldProof proof_,
		SceneLibrary& sceneLib_
	);

	//シーンの更新処理は代行してもらう
	void Run(NexusFieldProof proof_,AgentKey key_);


private:

	void ChangeScene(std::string const& next_);


	//現在稼働しているシーン
	SceneBehavior* curScene = nullptr;
	SceneLibrary& sceneLib;

	//このシーンで使用しているカメラ、モデル、ライトなどの情報
	SceneBehavior::Output output;
};

