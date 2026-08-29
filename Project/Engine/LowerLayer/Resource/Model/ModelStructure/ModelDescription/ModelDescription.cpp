#include "ModelDescription.h"

namespace
{
	auto const fileName = "ModelDescription.cpp";
}

ModelDescription::RenderState::RenderState
(
	RenderPassComponent::Pass pass_,
	std::vector<RenderStateComponent::BlendMode> blendModes_,
	RenderStateComponent::CullMode cullMode_,
	ShaderPathComponent::MeshType meshType_,
	ShaderPathComponent::MaterialType materialType_
) : blendModes(std::move(blendModes_)), pass(pass_), cullMode(cullMode_), meshType(meshType_), materialType(materialType_)
{
	std::string errorMsg{};

	if (blendModes.size() == 0) errorMsg += "「ブレンドモードが1つも設定されてない」";

	ErrorMessageOutput::Assert::DetectError(errorMsg.length() == 0, errorMsg, fileName);
}


ModelDescription::ModelDescription
(
	std::vector<ModelDescription::Common> const& commons_,
	std::vector<ModelDescription::Unique> const& uniques_,
	std::string modelName_,
	std::vector<ModelDescription::RenderState> const& renderStates_
) :commons(commons_), uniques(uniques_), modelName(modelName_), renderStates(renderStates_)
{
	std::string errorMsg{};

	if (renderStates.size() == 0)			errorMsg += "「renderStatesが空」";
	if (uniques.size() == 0)				errorMsg += "「uniquesが空」";
	if (commons.size() == 0)				errorMsg += "「commonsが空」";
	if(uniques.size() != commons.size())	errorMsg += "「uniquesとcommonsのサイズが違う(恐らくエンジンのせい)」";


	ErrorMessageOutput::Assert::DetectError(errorMsg.length() == 0, modelName_ +  errorMsg, fileName);
}
