#include "ModelDescription.h"

namespace
{
	auto const fileName = "ModelDescription.cpp";
}


ModelDescription::ModelDescription
(
	std::string modelName_,
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> const& perDrawIndices_,
	std::vector<ModelDescription::RenderState> const& renderStates_,
	std::vector<StructuredBufferModelData::MaterialGPU> materials_
) :perDrawIndices(perDrawIndices_), renderStates(renderStates_), materials(materials_)
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
				if 
				(
					((UINT)blendMode >= (UINT)RenderStateComponent::BlendMode::kCount) ||
					(blendMode == RenderStateComponent::BlendMode::kOffScreen)
				)errorMsg += "そのブレンドモードは選択不可";
			}
		}

		if ((UINT)renderState.pass >= (UINT)RenderPassComponent::Pass::kCount)
		{
			errorMsg += "「そのパスは選択不可(最低限処置)」";
		}

		if
		(
			renderState.meshType == ShaderPathComponent::MeshType::kOffscreen ||
			(UINT)renderState.meshType >= (UINT)ShaderPathComponent::MeshType::kCount
		)
		{
			errorMsg += "「そのMeshTypeは選択不可(最低限処置)」";
		}

		if
		(
			renderState.materialType == ShaderPathComponent::MaterialType::kOffscreen ||
			(UINT)renderState.materialType >= (UINT)ShaderPathComponent::MaterialType::kCount
		)
		{
			errorMsg += "「そのMaterialTypeは選択不可(最低限処置)」";
		}


	}

	ErrorMessageOutput::Assert::DetectError(errorMsg.length() == 0, modelName_ + errorMsg, fileName);

	if (renderStates.size() == 0)		errorMsg += "「renderStatesが空」";
	if (perDrawIndices.size() == 0)		errorMsg += "「perDrawIndicesが空」";

	ErrorMessageOutput::Assert::DetectError(errorMsg.length() == 0, modelName_ +  errorMsg, fileName);

	for (auto& renderState : renderStates)
	{
		renderState.modelName = modelName_ + "[0]";
	}
}
