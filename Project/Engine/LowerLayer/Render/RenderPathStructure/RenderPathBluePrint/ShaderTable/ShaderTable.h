#pragma once
#include "../RenderPathBluePrint.h"
#


//使用するシェーダーの名前をテーブルから読み取ります
struct RenderPathBluePrint::ShaderTable
{
	template<typename ShaderComponent>
	std::string Watch(ShaderComponent shaderComponent_, RenderPathComponent::Pass passType_);

};

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	ShaderPathComponent::MeshType meshType_,
	RenderPathComponent::Pass passType_
);

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	ShaderPathComponent::MaterialType materialType_,
	RenderPathComponent::Pass passType_
);
