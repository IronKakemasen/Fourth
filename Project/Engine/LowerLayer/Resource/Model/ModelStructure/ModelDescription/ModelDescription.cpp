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
	std::vector<ModelDescription::RenderState> const& modelDescRenderStates_
) :commons(modelDescCommons_), uniques(modelDescUniques_), modelName(modelName_), renderStates(modelDescRenderStates_)
{
	//空チェック
	ErrorMessageOutput::Assert::DetectError
	(
		(renderStates.size() > 0 && uniques.size() > 0 && commons.size() > 0),
		modelName_ + "のDescのどれかが空だすね",
		fileName
	);

	//renderStatesのチェック
	for (auto const& state : renderStates)
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
		uniques.size() == commons.size(),
		"ユニークと共通のサイズが違う(おおかたエンジンのせい)",
		fileName
	);

}
