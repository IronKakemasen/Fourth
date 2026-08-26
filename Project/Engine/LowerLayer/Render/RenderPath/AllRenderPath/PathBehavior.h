#pragma once
#include "../../RenderContext.h"
#include "../../RenderPass/AllRenderPass/AllPassFwd.h"

class RenderContext::PathBehavior
{
public:

	PathBehavior(NexusFieldProof proof_);
	virtual ~PathBehavior() = default;

	template<typename PassType>
	void AddPass(NexusFieldProof proof_ , PassType* pass_)
	{
		std::get<PassType*>(passses) = pass_;
	}

protected:
	//パフォーマンス稼ぎたいのでanyではなくtupleで
	AllPassPtr passses;
};

