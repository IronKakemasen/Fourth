#pragma once
#include "../ViewCreatorBehavior.h"

class SRV_Creator : public ViewCreatorBehavior<D3D12_SHADER_RESOURCE_VIEW_DESC>
{
public:
	SRV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	virtual void CreateView(GPUBufferBehavior& buffer_)override;


private:

	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateViewDesc()override;

};

