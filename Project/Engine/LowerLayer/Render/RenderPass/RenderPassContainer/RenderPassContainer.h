#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPass/AllPassInclude.h"

class RenderContext::RenderPassContainer
{
public:

	RenderPassContainer(NexusFieldProof proof_);
	~RenderPassContainer() = default;

	template<typename PassType>
	PassType* Import
	(
		NexusFieldProof proof_,
		std::unique_ptr<PassType>&& pass_
	)
	{
		auto* passPtr = pass_.get();
		std::get<std::unique_ptr<PassType>>(allPass) = std::move(pass_);

		return passPtr;
	}

	//被った時に渡す用
	template<typename PassType>
	PassType* Export(NexusFieldProof proof_)
	{
		return std::get<std::unique_ptr<PassType>>(allPass).get() ?
			std::get<std::unique_ptr<PassType>>(allPass).get() : nullptr;
	}


private:

	std::tuple
	<
		std::unique_ptr<SceneTextureCreator>
	>allPass;
};

