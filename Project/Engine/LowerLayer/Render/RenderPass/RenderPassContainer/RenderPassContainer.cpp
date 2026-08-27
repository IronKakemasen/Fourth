#include "PreCompileHeader.h"
#include "RenderPassContainer.h"

RenderContext::RenderPassContainer::RenderPassContainer(NexusFieldProof proof_)
{

}

std::unordered_map<RenderPassComponent::Pass, RenderContext::PassBehavior*> const& 
RenderContext::RenderPassContainer::AccessAllPassPtrMap(NexusFieldProof proof_)const
{
	return allPassPtrMap;
}
