#pragma once
#include "../DescriptorHeapContext.h"
#include "../DescriptorHeapPool/DescriptorHeapPool.h"

class DescriptorHeapContext::DescriptorHeapPoolContainer
{
public:
	DescriptorHeapPoolContainer(NexusFieldProof proof_);

	template<D3D12_DESCRIPTOR_HEAP_TYPE heapType>
	void Import(NexusFieldProof proof_, std::unique_ptr<DescriptorHeapPool>&& data_)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			container.find(heapType) == container.end(),
			"すでにそこにはでーたがある",
			"DescriptorHeapPoolContainer.h"
		);

		container[heapType] = std::move(data_);
	}


	template<D3D12_DESCRIPTOR_HEAP_TYPE heapType>
	DescriptorHeapPool* Export(NexusFieldProof proof_)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			container.find(heapType) != container.end(),
			"DescriptorHeapPoolContainerに設定していない識別子を検出",
			"DescriptorHeapPoolContainer.h"
		);

		return container[heapType].get();
	}


private:

	std::unordered_map < D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeapPool>> container;
};

