#include "PreCompileHeader.h"
#include "BufferRequiredInfo.h"


void RenderPath::Pass::RequiredBufferInfo::Add
(
	DXGI_FORMAT format_,
	std::array<float, 4> clearColor_,
	uint32_t width_,
	uint32_t height_,
	std::string name_
)
{
	name_ += "Texture";
	colorBuffers.emplace_back(format_, clearColor_, width_, height_, name_);
}

void RenderPath::Pass::RequiredBufferInfo::Add
(
	DXGI_FORMAT dsvFormat_,
	DXGI_FORMAT srvFormat_,
	float clearDepth_,
	float clearStencil_,
	std::string name_

)
{
	name_ += "DepthStencilTexture";
	depthStencilBuffer.emplace(dsvFormat_, srvFormat_, clearDepth_, clearStencil_, name_);

}
