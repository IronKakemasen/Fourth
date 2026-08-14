#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPass/AllPassFwd.h"

class RenderContext::RenderPassContainer
{
public:

	RenderPassContainer(NexusFieldProof proof_);

	template<typename PassType>
	PassType* Import(Local_CreateRenderPassLicence licence_ , std::unique_ptr<PassType>&& pass_);

private:

	std::vector<std::unique_ptr<RenderContext::PassBehavior>> allPass;
};



template<>
SceneTextureCreator* RenderContext::RenderPassContainer::Import
(
	Local_CreateRenderPassLicence licence_,
	std::unique_ptr<SceneTextureCreator>&& pass_
);
