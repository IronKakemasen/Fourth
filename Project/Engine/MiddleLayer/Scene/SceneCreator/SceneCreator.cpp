#include "PreCompileHeader.h"
#include "SceneCreator.h"


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




CameraContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveCameraSystems(CameraContextDiplomat& cameraContextDiplomat_)
{
	auto& agent = cameraContextDiplomat_.Access<CameraContext::ExecutionAgent>();
	
	return agent.DispatchFrontlineSystems(CameraContext::ExecutionAgent::SceneContextProof{});
}

ModelContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveModelSystems(ModelContextDiplomat& modelContextDiplomat_)
{
	auto& agent = modelContextDiplomat_.Access<ModelContext::ExecutionAgent>();

	return agent.DispatchFrontSystems(ModelContext::ExecutionAgent::SceneContextProof{});
}

GameObjectContext::FrontlineSystems* SceneContext::SceneCreator::ReceiveObjSystems(GameObjectContextDiplomat& gameObjectContextDiplomat_)
{
	auto& agent = gameObjectContextDiplomat_.Access<GameObjectContext::ExecutionAgent>();

	return agent.DispatchFrontlineSystems(GameObjectContext::ExecutionAgent::SceneContextProof{});

}
