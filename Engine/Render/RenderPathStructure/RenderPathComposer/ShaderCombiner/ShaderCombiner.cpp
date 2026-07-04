#include "PreCompileHeader.h"
#include "ShaderCombiner.h"

//外部
#include "../../../../Resource/Shader/ShaderLibrary/ShaderLibrary.h"


template<>
RenderPath::MS_PS RenderPath::PathComposer::ShaderCombiner::Combine
(
	ShaderLibrary* lib_, 
	RenderPathComponent::MeshType type_, 
	RenderPathComponent::Base base_
)
{
	RenderPath::MS_PS ms_ps;

	//ms_ps.first = lib_->Export(ShaderLibrary::GetDataKey{},)

	return ms_ps;
}

template<>
RenderPath::MS_PS RenderPath::PathComposer::ShaderCombiner::Combine
(
	ShaderLibrary* lib_, 
	RenderPathComponent::MaterialType type_,
	RenderPathComponent::Base base_
)
{
	RenderPath::MS_PS ms_ps;

	//ms_ps.first = lib_->Export(ShaderLibrary::GetDataKey{},)

	return ms_ps;

}
