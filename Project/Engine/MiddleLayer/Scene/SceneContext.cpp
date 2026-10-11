#include "PreCompileHeader.h"
#include "SceneContext.h"
#include "SceneLibrary/SceneLibrary.h"
#include "SceneCreator/SceneCreator.h"
#include "SceneContextRuntime/SceneController/SceneController.h"
#include "SceneContextRuntime/SceneDataBatchingPlace/SceneDataBatchingPlace.h"

#include "SceneContextDiplomat/SceneContextDiplomat.h"
#include "SceneContextDiplomat/SceneExecutionAgent/SceneExecutionAgent.h"

namespace
{
	std::string const fileName = "SceneContext.cpp";
}


SceneContext::SceneContext(NexusFieldProof proof_)
{
	Logger::Entry("SceneContext: Constructor");


	sceneLibrary = std::make_unique<SceneLibrary>(proof_);
	Logger::Log("Instantiate: SceneLibrary", fileName);

	sceneController = std::make_unique<SceneController>(proof_, *sceneLibrary);
	Logger::Log("Instantiate: SceneController", fileName);

	sceneCreator = std::make_unique<SceneCreator>(proof_, *sceneLibrary);
	Logger::Log("Instantiate: SceneCreator", fileName);


	diplomat = std::make_unique<SceneContextDiplomat>
	(
		proof_,
		std::make_unique<ExecutionAgent>(proof_, *sceneController)
	);
	Logger::Log("Instantiate: SceneContextDiplomat", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);


	Logger::End("SceneContext: Constructor");

}

SceneContext::~SceneContext()
{

}
