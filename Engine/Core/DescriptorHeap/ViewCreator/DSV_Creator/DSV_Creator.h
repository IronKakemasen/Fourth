#pragma once
#include "../ViewCreatorBehavior.h"


class DSV_Creator : public ViewCreatorBehavior
{
public:

	DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer_);

	//ビュー生成
	virtual void CreateView(GPUBufferBehavior& buffer_)override;

	//コマンドセット
	void SetCommand(std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DEPTH_STENCIL_VIEW_DESC, UINT, bool)> command_);

private:

	//DSV_descriptorHandleCPUコンテナのアドレス
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer;

	//ビュー生成コマンド
	std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DEPTH_STENCIL_VIEW_DESC, UINT, bool)> createViewCommand;


};

