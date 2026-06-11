#pragma once
#include "../ViewCreatorBehavior.h"


class DSV_Creator : public ViewCreatorBehavior<D3D12_DEPTH_STENCIL_VIEW_DESC>
{
public:

	DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	//ビュー生成
	virtual void CreateView(GPUBufferBehavior& buffer_)override;

private:


	virtual D3D12_DEPTH_STENCIL_VIEW_DESC CreateViewDesc()override;

};

