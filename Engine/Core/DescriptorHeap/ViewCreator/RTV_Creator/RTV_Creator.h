#pragma once
#include "../ViewCreatorBehavior.h"



//RTVを作る
class RTV_Creator : public ViewCreatorBehavior
{
public:

	RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer_);

	virtual void CreateView(GPUBufferBehavior& buffer_)override;

private:

	//RTV_descriptorHandleCPUコンテナのアドレス
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer;

	//ビュー生成コマンド
	std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> createViewCommand;

	//Viewdescの生成
	D3D12_RENDER_TARGET_VIEW_DESC CreateViewDesc();
	//コマンドセット
	void SetCommand(std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> command_);
};

