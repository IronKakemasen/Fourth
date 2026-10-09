#pragma once
#include "../CameraContext.h"


class CameraContextDiplomat
{
public:

	CameraContextDiplomat
	(
		CameraContext::NexusFieldProof proof_,
		std::unique_ptr<CameraContext::ExecutionAgent>&& executionAgent_
	);

	template<typename ToolType>
	auto& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}


private:

	std::tuple<std::unique_ptr<CameraContext::ExecutionAgent>> tools;

};

