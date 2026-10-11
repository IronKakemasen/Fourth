#pragma once
#include "../SceneContext.h"


class ModelContextDiplomat;
class CameraContextDiplomat;
class BufferContextDiplomat;

class SceneContext::ScenePipeline
{
	//ランタイムでシーンの制御を行う
	class SceneController;
	//そのシーンで使用しているデータのバッチング場
	class SceneDataBatchingPlace;

public:

	ScenePipeline(NexusFieldProof proof_,SceneLibrary& sceneLibrary_);
	~ScenePipeline();

	//シーンの更新処理の親玉
	//更新処理の呼び出しは代行でやってもらう
	void Run
	(
		NexusFieldProof proof_ ,
		AgentKey key_,
		UINT const frameIndex_,
		ModelContextDiplomat& modelContextDiplomat_,
		CameraContextDiplomat& cameraContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:
	std::unique_ptr<SceneController> sceneController;


};

