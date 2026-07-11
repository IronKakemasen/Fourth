#pragma once
#include "RenderPath.h"

#include "ShaderPathComponent.h"
#include "RenderStateComponent.h"
#include "RenderPassComponent .h"


struct RenderPath::Desc
{
	Desc
	(
		ShaderPathComponent::MeshType meshType_,
		ShaderPathComponent::MaterialType materialType_,
		RenderStateComponent::BlendMode blendMode_,
		RenderStateComponent::CullMode cullMode_,
		RenderStateComponent::FillMode fillMode_,
		RenderPassComponent ::Pass pass_
	) :meshType(meshType_), materialType(materialType_), blendMode(blendMode_), cullMode(cullMode_), fillMode(fillMode_), pass(pass_)
	{

	}

	ShaderPathComponent::MeshType meshType;
	ShaderPathComponent::MaterialType materialType;
	RenderStateComponent::BlendMode blendMode;
	RenderStateComponent::CullMode cullMode;
	RenderStateComponent::FillMode fillMode;
	RenderPassComponent ::Pass pass;

};