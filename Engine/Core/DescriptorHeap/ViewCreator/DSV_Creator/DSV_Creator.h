#pragma once
#include "../ViewCreatorBehavior.h"


class DSV_Creator : public ViewCreatorBehavior<D3D12_DEPTH_STENCIL_VIEW_DESC>
{
public:

	DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer_);

	//ビュー生成
	virtual void CreateView(GPUBufferBehavior& buffer_)override;

private:

	//DSV_descriptorHandleCPUコンテナのアドレス
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer;

	virtual D3D12_DEPTH_STENCIL_VIEW_DESC CreateViewDesc()override;

};

