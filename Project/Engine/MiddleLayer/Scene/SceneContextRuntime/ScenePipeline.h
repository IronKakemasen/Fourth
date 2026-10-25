#pragma once
#include "../SceneCreator/SceneCreator.h"

//外部
#include "../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/RenderStateKey.h"

class ModelContextDiplomat;
class CameraContextDiplomat;
class BufferContextDiplomat;

class Model;
struct RenderStateKey;

class SceneContext::ScenePipeline
{
	//ランタイムでシーンの制御を行う
	class SceneController;
	//そのシーンで使用しているデータのバッチング場
	class SceneDataBatchingPlace;
	//シーンのユニークを保管
	class SceneLibrary;

public:

	ScenePipeline(NexusFieldProof proof_);
	~ScenePipeline();

	SceneBehavior::Output const& WatchCurSceneOutput(AgentKey key_);

	//シーンの更新処理を呼ぶ
	//更新処理の呼び出しは代行でやってもらう
	void Run
	(
		NexusFieldProof proof_ ,
		AgentKey key_
	);

	//シーンデータのバッチングを行う
	void BatchSceneData
	(
		NexusFieldProof proof_,
		AgentKey key_,
		UINT const frameIndex_,
		ModelContextDiplomat& modelContextDiplomat_,
		CameraContextDiplomat& cameraContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	//シーンを作成する
	//エンジンインターフェースの初期化で呼び出される
	template<typename SceneType>
	void CreateScene
	(
		AgentKey key_,
		std::string const& sceneName_,
		CameraContextDiplomat& cameraContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_
	)
	{
		SceneCreator sceneCreator;

		ImportScene
		(
			sceneCreator.Create<SceneType>
			(
				cameraContextDiplomat_,
				modelContextDiplomat_
			),
			sceneName_
		);

		Logger::Log("Instantiate: " + sceneName_, "ScenePipeline.h");
	}

private:

	void ImportScene(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_);

	std::unique_ptr<SceneLibrary> sceneLibrary;
	std::unique_ptr<SceneController> sceneController;

};

