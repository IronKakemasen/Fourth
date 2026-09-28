
#include "BufferDescriptionBehavior.h"

BufferDescriptionBehavior::BufferDescriptionBehavior
(
	D3D12_RESOURCE_STATES initialState_,
	ProjectConfig::Render::NumBuffer numBuffer_ 
):initialState(initialState_), numBuffer(numBuffer_)
{

};
