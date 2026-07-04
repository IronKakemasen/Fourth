#pragma once
#include "RenderPathComponent.h"


///レンダーパスの設計図
namespace RenderPathBluePrint
{
	//使用するシェーダーの名前をテーブルから読み取ります
	struct ShaderTable
	{
		template<typename ShaderComponent>
		std::string Watch(ShaderComponent shaderComponent_, RenderPathComponent::Base baseType_);

	};



};


template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	RenderPathComponent::MeshType meshType_,
	RenderPathComponent::Base baseType_
);

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	RenderPathComponent::MeshType meshType_,
	RenderPathComponent::Base baseType_
);
