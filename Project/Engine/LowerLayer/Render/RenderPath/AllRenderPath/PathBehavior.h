#pragma once
#include "../../RenderContext.h"
#include "../../RenderPass/AllRenderPass/AllPassFwd.h"
#include "../../RenderStateComponent.h"
#include "../../RenderPass/AllRenderPass/RenderPassBehavior.h"


//外部
#include "../../../Buffer/BufferContext.h"

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

	virtual void Run
	(
		std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		RenderStateComponent::FillMode const modelFillMode_,
		PSO_PoolDispatcher& psoDispatcher_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	) = 0;

protected:

	//Passの更新処理を呼ぶ
	template<typename PassType>
	void CallPassUpdate
	(
		std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
		RenderStateComponent::FillMode const modelFillMode_,
		PSO_PoolDispatcher& psoDispatcher_,
		RuntimeWrapper& cmdWrapper_,
		BufferContext::BufferDispatcher& bufDispatcher_
	)
	{
		std::get<PassType*>(passses)->Update
		(
			modelContainer_,
			modelFillMode_,
			psoDispatcher_,
			cmdWrapper_,
			bufDispatcher_
		);
	}

	//名前。pathシーケンス初期化のために所持する
	std::string name;

	//パフォーマンス稼ぎたいのでanyではなくtupleで
	AllPassPtr passses;
};

