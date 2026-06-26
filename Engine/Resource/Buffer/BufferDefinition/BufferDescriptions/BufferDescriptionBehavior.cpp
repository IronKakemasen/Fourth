#include "PreCompileHeader.h"
#include "BufferDescriptionBehavior.h"

BufferDescriptionBehavior::BufferDescriptionBehavior
(
	D3D12_RESOURCE_STATES initialState_,
	ProjectConfig::Render::NumBuffer numBuffer_ = ProjectConfig::Render::NumBuffer::kSingleBuffer
):initialState(initialState_), numBuffer(numBuffer_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		(initialState != D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_Error_Detection),
		"リソースステートが初期化されていない", "BufferDescriptionBehavior.cpp"
	);
};
