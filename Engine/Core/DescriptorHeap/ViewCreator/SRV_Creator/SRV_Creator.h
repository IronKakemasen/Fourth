#pragma once
#include "../ViewCreatorBehavior.h"


//SRVを作る
class SRV_Creator : public ViewCreatorBehavior<D3D12_SHADER_RESOURCE_VIEW_DESC>
{
public:
	SRV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	virtual void CreateView(GPUBufferBehavior& buffer_, uint32_t allocateIndex_)override;


private:

	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateViewDesc()override;


};

