#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPass/AllPassFwd.h"
#include "../AllRenderPass/AllPassInclude.h"
#include "../AllRenderPass/RenderPassTraits.h"


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
		allPassPtrMap[RenderPassTraits::PassClassTraits<PassType>::passEnum] = passPtr;

		std::get<std::unique_ptr<PassType>>(allPassUnique) = std::move(pass_);

		return passPtr;
	}

	//被った時に渡す用
	template<typename PassType>
	PassType* Export(NexusFieldProof proof_)const
	{
		return std::get<std::unique_ptr<PassType>>(allPassUnique) ? 
			std::get<std::unique_ptr<PassType>>(allPassUnique).get() : nullptr;
	}

	//RenderGraphさんに全てのパスの情報を渡してPSOを作ってもらう
	std::unordered_map<RenderPassComponent::Pass,PassBehavior*> const& AccessAllPassPtrMap(NexusFieldProof proof_)const;

private:

	AllPassUnique allPassUnique;
	std::unordered_map<RenderPassComponent::Pass, PassBehavior*> allPassPtrMap;
};

