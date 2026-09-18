#pragma once
#include "../../RenderContext.h"

#include "../../../Core/Command/CommandContext.h"

class Model;

class RenderContext::PassBehavior
{
public:

	PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_);
	virtual ~PassBehavior() = default;

	PassDesc const& WatchDesc() const { return *desc; }

	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	) = 0;

protected:

	//Passの設計図
	std::unique_ptr<PassDesc> desc;
	//ランタイムで必要になるPassの情報をまとめたもの
	std::unique_ptr<RuntimePassInfo> runtimePassInfo;
};

