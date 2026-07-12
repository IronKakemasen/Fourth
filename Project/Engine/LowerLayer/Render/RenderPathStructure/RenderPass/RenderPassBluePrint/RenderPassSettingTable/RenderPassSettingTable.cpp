#include "PreCompileHeader.h"
#include "RenderPassSettingTable.h"


RenderPath::Pass::PassSettings RenderPassBluePrint::RenderPassSettingTable::SettingTable(RenderPassComponent::Pass pass_)
{
	RenderPath::Pass::PassSettings settings;

	switch (pass_)
	{
	case RenderPassComponent::Pass::kCreateSceneTexture:

		//当然
		settings.depthEnable = RenderPassComponent::DepthEnable::kEnable;
		//基本reverseZなんで
		settings.depthTest = RenderPassComponent::DepthTest::kGreaterEqual;

		break;

	case RenderPassComponent::Pass::kFinal:
		///ファイナルの責務はrenderContextではないので消す可能性が高い


		break;

	default:
		ErrorMessageOutput::Assert::OutputError("無効なPassです", "DepthConfigTable.cpp");

		break;

	}

	return settings;
}