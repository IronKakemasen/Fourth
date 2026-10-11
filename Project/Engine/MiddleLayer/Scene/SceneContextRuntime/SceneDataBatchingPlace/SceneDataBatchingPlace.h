#pragma once
#include "../ScenePipeline.h"


class SceneContext::ScenePipeline::SceneDataBatchingPlace
{
public:

	SceneDataBatchingPlace();

	//カメラやモデル、ライトなどのそのシーンで使用しているデータのバッチング場
	void BatchingPlace
	(
		UINT const frameIndex_,
		SceneController const& sceneController_,
		ModelContextDiplomat& modelContextDiplomat_,
		CameraContextDiplomat& cameraContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:


};

