#include "PreCompileHeader.h"
#include "RenderPassBehavior.h"
#include "RenderPassTraits.h"
#include "../PassDesc/PassDesc.h"
#include "../RuntimePassInfo/RuntimePassInfo.h"


RenderContext::PassBehavior::PassBehavior(NexusFieldProof proof_, std::unique_ptr<PassDesc>&& desc_)
	:desc(std::move(desc_))
{
	
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderContext::PassDesc const* RenderContext::PassBehavior::WatchDesc() const
{
	return desc ? desc.get() : nullptr;
}

void RenderContext::PassBehavior::CreatePassInfo
(
	NexusFieldProof proof_,
	std::unordered_map<std::string, BufferUniqueID> const& idMap_,
	UINT const refOffset_
) 
{
	runtimePassInfo.reset(new RuntimePassInfo(proof_, std::move(desc), idMap_, refOffset_));
}
