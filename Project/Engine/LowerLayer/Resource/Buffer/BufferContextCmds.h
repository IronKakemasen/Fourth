#pragma once
#include "../../../../Assets/Shared/ConstantBuffers.h"

class ConstantBuffer;

namespace BufferContextCmds
{
	using CreateCBufferCmd = std::function<std::pair<BufferUniqueID, ConstantBuffer*>
		(std::string name_, UINT const realDataSize_, ConstantBuffers::BindSlot const bindSlot_)>;

}
