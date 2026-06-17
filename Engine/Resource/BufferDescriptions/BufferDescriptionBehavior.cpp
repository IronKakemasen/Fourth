#include "PreCompileHeader.h"
#include "BufferDescriptionBehavior.h"

BufferDescriptionBehavior::BufferDescriptionBehavior(ResourceStates initialStates_) : initialStates(initialStates_)
{
	for (D3D12_RESOURCE_STATES state : initialStates)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			(state != D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_Error_Detection),
			"リソースステートが初期化されていない", "BufferDescriptionBehavior.cpp"
		);
	}

};
