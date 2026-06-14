#include "PreCompileHedder.h"
#include "BufferDescriptionBehavior.h"

BufferDescriptionBehavior::BufferDescriptionBehavior(D3D12_RESOURCE_STATES initialState_) : initialState(initialState_)
{
	if (initialState == D3D12_RESOURCE_STATE_Error_Detection)
	{
		ErrorMessageOutput::Assert::DetectError((initialState != D3D12_RESOURCE_STATE_Error_Detection),
			"初期ステート未設定", "BufferDescriptionBehavior.cpp");
	}
};
