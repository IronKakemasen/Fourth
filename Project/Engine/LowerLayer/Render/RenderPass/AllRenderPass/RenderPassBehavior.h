#pragma once
#include "../../RenderContext.h"

#include "../../../Core/Command/CommandContext.h"

class Model;

class RenderContext::PassBehavior
{
public:

	PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_);
	virtual ~PassBehavior() = default;

	virtual void Update
	(
		[[maybe_unused]] std::vector<Model> const& modelContainer_,
		CommandContext::RuntimeWrapper& cmdWrapper_
	) = 0;

	PassDesc const* WatchDesc() const;
	void CreatePassInfo
	(
		NexusFieldProof proof_,
		std::unordered_map<std::string, BufferUniqueID> const& idMap_,
		UINT const refOffset_
	);

protected:

	//Passの設計図
	std::unique_ptr<PassDesc> desc;
	//ランタイムで必要になるPassの情報をまとめたもの
	std::unique_ptr<RuntimePassInfo> runtimePassInfo;
};

