#include "PreCompileHeader.h"
#include "SceneExecutionAgent.h"
#include "../../SceneContextRuntime/ScenePipeline.h"


SceneContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, ScenePipeline& scenePipeline_)
	:scenePipeline(scenePipeline_)
{

}


void SceneContext::ExecutionAgent::RunScenePipeline
(
	NexusFieldProof proof_,
	UINT const frameIndex_,
	ModelContextDiplomat& modelContextDiplomat_,
	CameraContextDiplomat& cameraContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	scenePipeline.Run
	(
		proof_, 
		AgentKey{},
		frameIndex_, 
		modelContextDiplomat_, 
		cameraContextDiplomat_, 
		bufferContextDiplomat_
	);
}
