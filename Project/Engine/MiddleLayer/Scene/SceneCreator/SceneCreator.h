#pragma once
#include "../SceneContext.h"
#include "../SceneStructure/SceneBehavior.h"

//外部
#include "../../../LowerLayer/Resource/Camera/CameraContext.h"

#include "../../../LowerLayer/Resource/Model/ModelContext.h"

#include "../../../../Application/AllSceneIncludes.h"



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

	//シーンの本体はいただく
	void Import(std::unique_ptr<SceneBehavior>&& scene_, std::string const& sceneName_);

	//CameraFrontlineSystemsを一つもらう
	CameraContext::CameraFrontlineSystems& ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_);
	//ModelFrontlineSystemsを一つもらう
	ModelContext::ModelFrontlineSystems& ReceiveModelSystems(ModelContextDiplomat& modelContextDiplomat_);

	SceneLibrary& sceneLib;

};

