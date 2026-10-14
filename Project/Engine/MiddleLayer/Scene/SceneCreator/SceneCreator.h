#pragma once
#include "../SceneContext.h"

//外部
#include "../SceneStructure/SceneBehavior.h"
#include "../../../../Application/AllSceneIncludes.h"
#include "../../../LowerLayer/Resource/Camera/CameraContext.h"


class CameraContextDiplomat;

//CameraFrontlineSystems
class SceneContext::SceneCreator
{
public:
	SceneCreator(NexusFieldProof proof_,SceneLibrary& sceneLib_);

	//シーンを作成する
	template<typename SceneType>
	void Create(std::string const& sceneName_, CameraContextDiplomat& cameraContextDiplomat_)
	{
		Logger::Log("Create Scene: " + sceneName_, "SceneCreator.h");

		Import
		(
			std::move(std::make_unique<SceneType>(ReceiveCameraSystems(cameraContextDiplomat_))),
			sceneName_
		);
	}

private:

	void Import(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_);
	CameraContext::CameraFrontlineSystems& ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_);

	SceneLibrary& sceneLib;

};

