#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPass/AllPassFwd.h"


class RenderContext::RenderPassCreator
{
	class PassDescAssembler;

public:

	RenderPassCreator(NexusFieldProof proof_,RenderPassContainer* container_);

	template<typename PassType>
	PassType* Create
	(
		Local_CreateRenderPassLicence licence_,
		const PassDesc& desc_
	);

private:

	RenderPassContainer* passContainer;
};

template<>
SceneTextureCreator* RenderContext::RenderPassCreator::Create
(
	Local_CreateRenderPassLicence licence_,
	const PassDesc& desc_
);
