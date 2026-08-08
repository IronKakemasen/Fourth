#pragma once

class ConstantBuffer;

namespace BufferContextCmds
{
	using CreateCBufferCmd = std::function<std::pair<BufferUniqueID, ConstantBuffer*>
		(std::string name_, UINT const realDataSize_, const uint8_t bindSlot_)>;

}
