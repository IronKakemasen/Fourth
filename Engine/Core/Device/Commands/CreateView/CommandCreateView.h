#pragma once
#include "../DeviceContextCommandBehavior.h"


//Resourceのビューを生成するコマンド
struct CommandCreateView : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandGeneratorクラスのみ生成可能
	CommandCreateView(DeviceContext::CommandGenerator::GenerateKey generateKey_);
	~CommandCreateView();

	void CreateRTV(ID3D12Device8* device_, ID3D12Resource* resource_ , const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);
	void CreateSRV(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);
	void CreateDSV(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_);

};

