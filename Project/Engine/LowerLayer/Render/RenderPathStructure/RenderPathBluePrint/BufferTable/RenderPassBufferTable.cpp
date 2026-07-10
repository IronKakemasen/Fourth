#include "PreCompileHeader.h"
#include "RenderPassBufferTable.h"


RenderPathBluePrint::BufferTable::RequiredBufferInfo RenderPathBluePrint::BufferTable::BufferInfoTable(RenderPathComponent::Pass pass_)
{
	RenderPathBluePrint::BufferTable::RequiredBufferInfo info;

	switch (pass_)
	{
	case RenderPathComponent::Pass::kCreateSceneTexture:
		
		info.Add
		(
			DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			{ 0.0f,0.0f, 0.0f, 0.0f },
			ProjectConfig::Window::kWidth,
			ProjectConfig::Window::kHeight
		);

		info.Add
		(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			0.0f,
			0.0f
		);

		break;

	case RenderPathComponent::Pass::kFinal:
		///FinalPassは特にすることないかな

		break;
	
	default:

		ErrorMessageOutput::Assert::OutputError("不明なPassです", "RequiredBufferInfo.cpp");

		break;
	}

	return info;
}



void RenderPathBluePrint::BufferTable::RequiredBufferInfo::Add
(
	DXGI_FORMAT format_,
	std::array<float, 4> clearColor_,
	uint32_t width_,
	uint32_t height_
)
{
	colorBuffers.emplace_back(format_, clearColor_, width_, height_);
}

void RenderPathBluePrint::BufferTable::RequiredBufferInfo::Add
(
	DXGI_FORMAT dsvFormat_,
	DXGI_FORMAT srvFormat_,
	float clearDepth_,
	float clearStencil_
)
{
	depthStencilBuffer.emplace(dsvFormat_, srvFormat_, clearDepth_, clearStencil_);

}
