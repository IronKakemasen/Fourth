#pragma once
#include "../ViewCreatorBehavior.h"


class DSV_Creator : public ViewCreatorBehavior
{
public:

	DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	virtual [[nodiscard]] uint32_t CreateView(const GPUBufferBehavior& buffer_)override;

};

