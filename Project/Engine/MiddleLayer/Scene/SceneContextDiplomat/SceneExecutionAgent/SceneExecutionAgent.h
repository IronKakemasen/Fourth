#pragma once
#include "../../SceneContext.h"


class ModelContextDiplomat;
class CameraContextDiplomat;
class BufferContextDiplomat;

class SceneContext::ExecutionAgent
{

public:

	ExecutionAgent(NexusFieldProof proof_, ScenePipeline& scenePipeline_);

	void RunScenePipeline
	(
		NexusFieldProof proof_,
		UINT const frameIndex_,
		ModelContextDiplomat& modelContextDiplomat_,
		CameraContextDiplomat& cameraContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:

	ScenePipeline& scenePipeline;
};

