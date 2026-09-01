#include "ModelDescription.h"

namespace
{
	auto const fileName = "ModelDescription.cpp";
}


ModelDescription::ModelDescription
(
	std::string modelName_,
	std::vector<ModelDescription::Common> const& commons_,
	std::vector<ModelDescription::Unique> const& uniques_,
	std::vector<ModelDescription::RenderState> const& renderStates_
) :commons(commons_), uniques(uniques_), renderStates(renderStates_)
{
	std::string errorMsg{};

	for (auto& renderState : renderStates)
	{
		if (renderState.blendModes.size() == 0)
		{
			errorMsg += "「ブレンドモードが1つも設定されてない」";
		}
		else
		{
			for (auto const& blendMode : renderState.blendModes)
			{
				if ((UINT)blendMode >= (UINT)RenderStateComponent::BlendMode::kCount)errorMsg += "そのブレンドモードは選択不可";
			}
		}

		if ((UINT)renderState.pass >= (UINT)RenderPassComponent::Pass::kCount)
		{
			errorMsg += "「そのパスは選択不可(最低限処置)」";
		}
	}

	ErrorMessageOutput::Assert::DetectError(errorMsg.length() == 0, modelName_ + errorMsg, fileName);

	if (renderStates.size() == 0)			errorMsg += "「renderStatesが空」";
	if (uniques.size() == 0)				errorMsg += "「uniquesが空」";
	if (commons.size() == 0)				errorMsg += "「commonsが空」";
	if(uniques.size() != commons.size())	errorMsg += "「uniquesとcommonsのサイズが違う(恐らくエンジンのせい)」";

	ErrorMessageOutput::Assert::DetectError(errorMsg.length() == 0, modelName_ +  errorMsg, fileName);

	for (auto& renderState : renderStates)
	{
		renderState.modelName = modelName_ + "[0]";
	}
}
