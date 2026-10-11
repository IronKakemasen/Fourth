#pragma once
#include "../SceneContext.h"

//外部
#include "../../../../Application/AllSceneIncludes.h"
#include "../../../LowerLayer/Resource/Camera/CameraContext.h"


class SceneBehavior;

//CameraFrontlineSystems
class SceneContext::SceneCreator
{
public:
	SceneCreator(NexusFieldProof proof_,SceneLibrary& sceneLib_);

	template<typename SceneType>
	void Create(std::string const& sceneName_, CameraContextDiplomat& cameraContextDiplomat_)
	{
		Import
		(
			std::make_unique<SceneType>(ReceiveCameraSystems(cameraContextDiplomat_)),
			sceneName_
		);
	}

	SceneLibrary& sceneLib;

private:

	void Import(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_);
	CameraContext::CameraFrontlineSystems* ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_);
};

