#include "RenderPathBluePrint.h"

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	RenderPathComponent::MeshType meshType_,
	RenderPathComponent::Base baseType_
)
{
	return {};
}

template<>
std::string RenderPathBluePrint::ShaderTable::Watch
(
	RenderPathComponent::MaterialType meshType_,
	RenderPathComponent::Base baseType_
)
{
	return {};
}
