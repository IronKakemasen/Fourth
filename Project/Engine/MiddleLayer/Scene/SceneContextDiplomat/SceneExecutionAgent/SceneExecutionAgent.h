#pragma once
#include "../../SceneContextRuntime/ScenePipeline.h"


class ModelContextDiplomat;
class CameraContextDiplomat;
class BufferContextDiplomat;

class SceneContext::ExecutionAgent
{

public:

	struct EngineInterfaceProof;

	ExecutionAgent(NexusFieldProof proof_, ScenePipeline& scenePipeline_);

	void RunScenePipeline
	(
		NexusFieldProof proof_,
		UINT const frameIndex_,
		ModelContextDiplomat& modelContextDiplomat_,
		CameraContextDiplomat& cameraContextDiplomat_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	template<typename SceneType>
	void CreateScene
	(
		std::string const& sceneName_,
		CameraContextDiplomat& cameraContextDiplomat_,
		ModelContextDiplomat& modelContextDiplomat_
	)
	{
		scenePipeline.CreateScene<SceneType>
		(
			AgentKey{},
			sceneName_,
			cameraContextDiplomat_,
			modelContextDiplomat_
		);
	}




private:

	ScenePipeline& scenePipeline;
};

