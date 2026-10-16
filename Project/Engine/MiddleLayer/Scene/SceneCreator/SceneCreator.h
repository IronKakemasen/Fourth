#pragma once
#include "../SceneContext.h"

//外部
#include "../../../LowerLayer/Resource/Camera/CameraContext.h"

#include "../../../LowerLayer/Resource/Model/ModelContext.h"

class SceneBehavior;


//CameraFrontlineSystems
class SceneContext::SceneCreator
{
public:
	SceneCreator() = default;

	//シーンを作成する
	template<typename SceneType>
	std::unique_ptr<SceneType> Create
	(
		CameraContextDiplomat& cameraContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_
	)
	{
		return std::make_unique<SceneType>
		(
			ReceiveCameraSystems(cameraContextDiplomat_),
			ReceiveModelSystems(modelContextDiplomat_)
		);
	}

private:

	//CameraFrontlineSystemsを一つもらう
	CameraContext::CameraFrontlineSystems& ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_);
	//ModelFrontlineSystemsを一つもらう
	ModelContext::ModelFrontlineSystems& ReceiveModelSystems(ModelContextDiplomat& modelContextDiplomat_);


};

