#include "PreCompileHeader.h"
#include "SceneContext.h"
#include "SceneContextRuntime/ScenePipeline.h"
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


	scenePipeline = std::make_unique<ScenePipeline>(proof_);
	Logger::Log("Instantiate: ScenePipeline", fileName);

	diplomat = std::make_unique<SceneContextDiplomat>
	(
		proof_,
		std::make_unique<ExecutionAgent>(proof_, *scenePipeline)
	);
	Logger::Log("Instantiate: SceneContextDiplomat", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);


	Logger::End("SceneContext: Constructor");

}

SceneContext::~SceneContext()
{

}
