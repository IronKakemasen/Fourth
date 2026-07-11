#include "PreCompileHeader.h"
#include "DepthConfigTable.h"


RenderPassBluePrint::DepthTable::DepthConfig RenderPassBluePrint::DepthTable::DepthConfigTable(RenderPassComponent::Pass pass_)
{
	DepthConfig depthConfig;

	switch (pass_)
	{
	case RenderPassComponent::Pass::kCreateSceneTexture:

		//当然
		depthConfig.depthEnable = RenderPassComponent::DepthEnable::kEnable;
		//基本reverseZなんで
		depthConfig.depthTest = RenderPassComponent::DepthTest::kGreaterEqual;

		break;

	case RenderPassComponent::Pass::kFinal:
		///ファイナルの責務はrenderContextではないので消す可能性が高い


		break;

	default:
		ErrorMessageOutput::Assert::OutputError("無効なPassです", "DepthConfigTable.cpp");

		break;

	}

	return depthConfig;
}