#pragma once
#include "../../RenderContext.h"
#include "../../RenderPass/AllRenderPass/AllPassFwd.h"


class Model;
struct RenderStateKey;
class RuntimeWrapper;

class RenderContext::PathBehavior
{
public:

	PathBehavior(NexusFieldProof proof_,std::string const& name_);
	virtual ~PathBehavior() = default;

	//PathCreatorがジェーソンファイルから使用するPassを詰めてくれる
	template<typename PassType>
	void AddPass(NexusFieldProof proof_ , PassType* pass_)
	{
		std::get<PassType*>(passses) = pass_;
	}

	auto const& WatchName()const { return  name; }

	virtual void Update
	(
		[[maybe_unused]] std::pair<RenderStateKey, std::vector<Model*>> const& modelContainer_,
		RuntimeWrapper& cmdWrapper_
	) = 0;

protected:
	//名前。初期化のために所持する
	std::string name;


	//パフォーマンス稼ぎたいのでanyではなくtupleで
	AllPassPtr passses;
};

