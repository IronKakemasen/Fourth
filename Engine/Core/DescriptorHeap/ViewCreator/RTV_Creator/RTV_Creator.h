#pragma once
#include "../ViewCreatorBehavior.h"

class RTV_Creator : public ViewCreatorBehavior
{
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer;

public:
	RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer_);

	virtual [[nodiscard]] uint32_t CreateView(const GPUBufferBehavior& buffer_)override;

};

