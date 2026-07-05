#pragma once
#include "RenderPathComponent.h"


///レンダーパスの設計図
namespace RenderPathBluePrint
{
	//使用するシェーダーの名前をテーブルから読み取ります
	struct ShaderTable
	{
		template<typename ShaderComponent>
		std::string Watch(ShaderComponent shaderComponent_, RenderPathComponent::PathType pathType_);

	};



};


template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	RenderPathComponent::MeshType meshType_,
	RenderPathComponent::PathType pathType_
);

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	RenderPathComponent::MaterialType materialType_,
	RenderPathComponent::PathType pathType_
);
