#pragma once
#include "../DeviceContextCommandBehavior.h"


//Resourceのビューを生成するコマンド
struct CommandCreateView : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandCreateView(DeviceContext::GenerateKey generateKey_);

	template<typename ViewType>
	void CreateView(ID3D12Device8* device_, ID3D12Resource* resource_, const ViewType* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);

	void CreateUAV(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* counterResource_ = nullptr);

};

template<>
void CommandCreateView::CreateView(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);
template<>
void CommandCreateView::CreateView(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);
template<>
void CommandCreateView::CreateView(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);
