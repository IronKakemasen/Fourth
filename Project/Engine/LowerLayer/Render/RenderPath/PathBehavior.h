#pragma once
#include "../RenderContext.h"
#include "../RenderPass/AllRenderPass/AllPassFwd.h"

class RenderContext::PathBehavior
{
public:

	PathBehavior(NexusFieldProof proof_);
	
	template<typename PassType>
	void SetPass(NexusFieldProof proof_ , PassType* pass_)
	{
		std::get<PassType*>(passses) = pass_;
	}

protected:
	//パフォーマンス稼ぎたいのでanyではなくtupleで
	std::tuple<SceneTextureCreator*> passses;
};

