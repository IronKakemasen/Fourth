#include "PreCompileHeader.h"
#include "GameObjectContextDiplomat.h"
#include "GameObjectAgent/GameObjectAgent.h"


GameObjectContextDiplomat::GameObjectContextDiplomat
(
	GameObjectContext::NexusFieldProof proof_,
	std::unique_ptr<GameObjectContext::ExecutionAgent>&& executionAgent_
)
{
	std::get<std::unique_ptr<GameObjectContext::ExecutionAgent>>(tools) = std::move(executionAgent_);
}
