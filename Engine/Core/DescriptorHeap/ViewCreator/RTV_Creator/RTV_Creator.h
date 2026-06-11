#pragma once
#include "../ViewCreatorBehavior.h"



//RTVを作る
class RTV_Creator : public ViewCreatorBehavior<D3D12_RENDER_TARGET_VIEW_DESC>
{
public:

	RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	virtual void CreateView(GPUBufferBehavior& buffer_)override;

private:

	virtual D3D12_RENDER_TARGET_VIEW_DESC CreateViewDesc()override;

};

