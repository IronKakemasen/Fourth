#pragma once
#include "../RenderPassBluePrint.h"
#


//使用するシェーダーの名前をテーブルから読み取ります
struct RenderPassBluePrint::ShaderTable
{
	template<typename ShaderComponent>
	std::string Watch(ShaderComponent shaderComponent_, RenderPassComponent ::Pass passType_);

};

template<>
std::string RenderPassBluePrint::ShaderTable::Watch
(
	ShaderPathComponent::MeshType meshType_,
	RenderPassComponent ::Pass passType_
);

template<>
std::string RenderPassBluePrint::ShaderTable::Watch
(
	ShaderPathComponent::MaterialType materialType_,
	RenderPassComponent ::Pass passType_
);
