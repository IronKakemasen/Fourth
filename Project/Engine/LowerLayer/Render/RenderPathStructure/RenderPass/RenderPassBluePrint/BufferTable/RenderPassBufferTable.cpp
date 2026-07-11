#include "PreCompileHeader.h"
#include "RenderPassBufferTable.h"


std::unique_ptr<RenderPath::Pass::RequiredBufferInfo> RenderPassBluePrint::BufferTable::BufferInfoTable(RenderPassComponent ::Pass pass_)
{
	std::unique_ptr<RenderPath::Pass::RequiredBufferInfo> info(new RenderPath::Pass::RequiredBufferInfo);

	switch (pass_)
	{
	case RenderPassComponent ::Pass::kCreateSceneTexture:
		
		info->Add
		(
			DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			{ 0.0f,0.0f, 0.0f, 0.0f },
			ProjectConfig::Window::kWidth,
			ProjectConfig::Window::kHeight,
			"scene"
		);

		info->Add
		(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			0.0f,
			0.0f,
			"scene"
		);

		break;

	case RenderPassComponent ::Pass::kFinal:
		///FinalPassは特にすることないかな

		break;
	
	default:

		ErrorMessageOutput::Assert::OutputError("不明なPassです", "RequiredBufferInfo.cpp");

		break;
	}

	return std::move(info);
}



