#include "ModelDescription.h"

namespace
{
	auto const fileName = "ModelDescription.cpp";
}

ModelDescription::ModelDescription
(
	std::vector<ModelDescription::Common> const& modelDescCommons_,
	std::vector<ModelDescription::Unique> const& modelDescUniques_,
	std::string modelName_,
	std::vector<ModelDescription::RenderStates> const& modelDescRenderStates_
) :modelDescCommons(modelDescCommons_), modelDescUniques(modelDescUniques_), modelName(modelName_), modelDescRenderStates(modelDescRenderStates_)
{
	//空チェック
	ErrorMessageOutput::Assert::DetectError
	(
		(modelDescRenderStates.size() > 0 && modelDescUniques.size() > 0 && modelDescCommons.size() > 0),
		modelName_ + "のDescのどれかが空だすね",
		fileName
	);

	//renderStatesのチェック
	for (auto const& state : modelDescRenderStates)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			(state.blendModes.size() > 0) && (state.passes != RenderStateComponent::RenderPass::kNone),
			modelName_ + "のModelDescription::RenderStatesのデータがちゃんと埋まってない(あなたのせい)",
			fileName
		);
	}

	//ユニークと共通の比がおなじかチェックしておく
	ErrorMessageOutput::Assert::DetectError
	(
		modelDescUniques.size() == modelDescCommons.size(),
		"ユニークと共通のサイズが違う(おおかたエンジンのせい)",
		fileName
	);

}
