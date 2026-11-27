#include "PreCompileHeader.h"
#include "SceneCreator.h"
#include "SceneConfigLoder/SceneConfigLoder.h"


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextDiplomat/CameraContextDiplomat.h"
#include "../../../LowerLayer/Resource/Camera/CameraContextDiplomat/CameraContextExecutionAgent/CameraContextExecutionAgent.h"
#include "../../../LowerLayer/Resource/Camera/CameraContextDiplomat/CameraContextExecutionAgent/CameraContextAgentLicences.h"

#include "../../../LowerLayer/Resource/Model/ModelContextDiplomat/ModelContextDiplomat.h"
#include "../../../LowerLayer/Resource/Model/ModelContextDiplomat/ModelContextExecutionAgent/ModelContextExecutionAgent.h"
#include "../../../LowerLayer/Resource/Model/ModelContextDiplomat/ModelContextExecutionAgent/ModelAgentLicences.h"

#include "../../GameObject/GameObjectContextDiplomat/GameObjectContextDiplomat.h"
#include "../../GameObject/GameObjectContextDiplomat/GameObjectAgent/GameObjectAgent.h"
#include "../../GameObject/GameObjectContextDiplomat/GameObjectAgent/GameObjectAgentLicences.h"

#include "../../../LowerLayer/Resource/Material/MaterialContextDiplomat/MaterialContextDiplomat.h"
#include "../../../LowerLayer/Resource/Material/MaterialContextDiplomat/MaterialExecutionAgent/MaterialAgentLicences.h"
#include "../../../LowerLayer/Resource/Material/MaterialContextDiplomat/MaterialExecutionAgent/MaterialExecutionAgent.h"

std::unique_ptr<SceneBehavior::SceneConfig> SceneContext::SceneCreator::LoadSceneConfig(std::string const& sceneName_)
{
	return SceneConfigLoder::Load(sceneName_);
}

template<>
CameraContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(CameraContextDiplomat& diplomat_)
{
	auto& agent = diplomat_.Access<CameraContext::ExecutionAgent>();

	return agent.DispatchFrontlineSystems(CameraContext::ExecutionAgent::SceneContextProof{});
}

template<>
ModelContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(ModelContextDiplomat& diplomat_)
{
	auto& agent = diplomat_.Access<ModelContext::ExecutionAgent>();

	return agent.DispatchFrontSystems(ModelContext::ExecutionAgent::SceneContextProof{});
}

template<>
GameObjectContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(GameObjectContextDiplomat& diplomat_)
{
	auto& agent = diplomat_.Access<GameObjectContext::ExecutionAgent>();

	return agent.DispatchFrontlineSystems(GameObjectContext::ExecutionAgent::SceneContextProof{});
}

template<>
MaterialContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveSystems(MaterialContextDiplomat& diplomat_)
{
	auto& agent = diplomat_.Access<MaterialContext::ExecutionAgent>();

	return agent.DispatchFrontlineSystems(MaterialContext::ExecutionAgent::SceneContextProof{});
}


