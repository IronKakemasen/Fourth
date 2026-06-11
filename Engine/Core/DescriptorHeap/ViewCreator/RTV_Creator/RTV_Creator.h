#pragma once
#include "../ViewCreatorBehavior.h"



//RTVを作る
class RTV_Creator : public ViewCreatorBehavior<D3D12_RENDER_TARGET_VIEW_DESC>
{
public:

	RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer_);

	virtual void CreateView(GPUBufferBehavior& buffer_, uint32_t allocateIndex_)override;

private:

	//RTV_descriptorHandleCPUコンテナのアドレス
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer;

	virtual D3D12_RENDER_TARGET_VIEW_DESC CreateViewDesc()override;

};

