#pragma once
#include "../ViewCreatorBehavior.h"


//SRV、UAVを同一のディスクリプタヒープ上に作る。
class UAV_Creator : public ViewCreatorBehavior< D3D12_UNORDERED_ACCESS_VIEW_DESC>
{
public:
	UAV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_);

	virtual void CreateView(GPUBufferBehavior& buffer_)override;


private:

	virtual D3D12_UNORDERED_ACCESS_VIEW_DESC CreateViewDesc()override;

};

