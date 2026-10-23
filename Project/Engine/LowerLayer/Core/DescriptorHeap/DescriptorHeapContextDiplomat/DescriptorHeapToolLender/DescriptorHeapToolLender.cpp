#include "PreCompileHeader.h"
#include "DescriptorHeapToolLender.h"
#include "../../DescriptorHeapPoolContainer/DescriptorHeapPoolContainer.h"

DescriptorHeapContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	DescriptorHeapContext::ViewCreator* viewCretator_,
	DescriptorHeapPoolContainer& descriptorHeapPoolContainer_
) 
{
	std::get<DescriptorHeapContext::ViewCreator*>(tools) = viewCretator_;
	std::get<ID3D12DescriptorHeap*>(tools) = 
		descriptorHeapPoolContainer_.Export<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(proof_)->AccessHeap(proof_);
}
