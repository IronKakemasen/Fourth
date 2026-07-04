#pragma once
#include "../RenderPathComposer.h"
#include "../../RenderPathComponent.h"

struct RenderPath::PathComposer::ShaderCombiner
{
	template<typename Type>
	RenderPath::MS_PS Combine(ShaderLibrary* lib_, Type type_, RenderPathComponent::Base base_);

};

template<>
RenderPath::MS_PS RenderPath::PathComposer::ShaderCombiner::Combine
(
	ShaderLibrary* lib_, 
	RenderPathComponent::MeshType type_,
	RenderPathComponent::Base base_
);

template<>
RenderPath::MS_PS RenderPath::PathComposer::ShaderCombiner::Combine
(
	ShaderLibrary* lib_, 
	RenderPathComponent::MaterialType type_,
	RenderPathComponent::Base base_
);
