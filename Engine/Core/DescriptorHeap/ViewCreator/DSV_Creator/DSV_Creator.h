#pragma once
#include "../ViewCreatorBehavior.h"


class DSV_Creator : public ViewCreatorBehavior
{
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer;

public:

	DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer_);

	virtual [[nodiscard]] uint32_t CreateView(const GPUBufferBehavior& buffer_)override;

};

