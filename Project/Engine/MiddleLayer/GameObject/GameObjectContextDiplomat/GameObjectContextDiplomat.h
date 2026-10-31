#pragma once
#include "../GameObjectContext.h"


class GameObjectContextDiplomat
{
public:

	GameObjectContextDiplomat
	(
		GameObjectContext::NexusFieldProof proof_,
		std::unique_ptr<GameObjectContext::ExecutionAgent>&& executionAgent_
	);

	template<typename ToolType>
	ToolType& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}


private:

	std::tuple
	<
		std::unique_ptr<GameObjectContext::ExecutionAgent>
	>tools;

};

