#pragma once
#include "ShaderPathComponent.h"
#include "../../Render/RenderPass/RenderPassComponent.h"

///MeshType X Pass = MeshShader
///MaterialType X Pass = PixelShader

namespace ShaderTable
{
	std::string const GetMeshShader(RenderPassComponent::Pass pass_, ShaderPathComponent::MeshType meshType_)
	{
		std::string meshShader;

		switch (pass_)
		{
		case RenderPassComponent::Pass::kSceneTextureCreatorOpaque:

			if (meshType_ == ShaderPathComponent::MeshType::kStatic)meshShader = "StaticMS";

			break;

		default:

			ErrorMessageOutput::Assert::DetectError
			(
				meshShader.size() > 0,
				"指定したRenderPassもしかしてオフスク用じゃない？(メッシュシェーダ)",
				"ShaderTable.h"
			);

			break;
		}

		ErrorMessageOutput::Assert::OutputError
		(
			"shaderTableにて設定外の組み合わせがきた(メッシュシェーダ)",
			"ShaderTable.h"
		);

		return meshShader;
	}

	std::string const GetPixelShader(RenderPassComponent::Pass pass_, ShaderPathComponent::MaterialType materialType_)
	{
		std::string pixelShader;

		switch (pass_)
		{
		case RenderPassComponent::Pass::kSceneTextureCreatorOpaque:

			if (materialType_ == ShaderPathComponent::MaterialType::kStandard)pixelShader = "StandardPS";

			break;

		default:

			ErrorMessageOutput::Assert::OutputError
			(
				"指定したRenderPassもしかしてオフスク用じゃない？(ピクセルシェーダ)",
				"ShaderTable.h"
			);

			break;
		}


		ErrorMessageOutput::Assert::DetectError
		(
			pixelShader.size() > 0,
			"shaderTableにて設定外の組み合わせがきた(ピクセルシェーダ)",
			"ShaderTable.h"
		);

		return pixelShader;
	}



}