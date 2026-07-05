#pragma once
#include "../ShaderPathComponent.h"


///レンダーパスの設計図
namespace RenderPathBluePrint
{
	//使用するシェーダーの名前をテーブルから読み取ります
	struct ShaderTable
	{
		template<typename ShaderComponent>
		std::string Watch(ShaderComponent shaderComponent_, ShaderPathComponent::Pass pathType_);

	};



};


template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	ShaderPathComponent::MeshType meshType_,
	ShaderPathComponent::Pass pathType_
);

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	ShaderPathComponent::MaterialType materialType_,
	ShaderPathComponent::Pass pathType_
);
