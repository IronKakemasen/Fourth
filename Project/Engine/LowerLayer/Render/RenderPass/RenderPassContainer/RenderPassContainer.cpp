#include "PreCompileHeader.h"
#include "RenderPassContainer.h"
#include "../AllRenderPass/SceneTextureCreator/SceneTextureCreator.h"


RenderContext::RenderPassContainer::RenderPassContainer(NexusFieldProof proof_)
{

}


template<>
SceneTextureCreator* RenderContext::RenderPassContainer::Import
(
	NexusFieldProof proof_,
	std::unique_ptr<SceneTextureCreator>&& pass_
)
{
	auto* passPtr = pass_.get();
	allPass.emplace_back(std::move(pass_));

	return passPtr;
}
