#include "PreCompileHedder.h"
#include "CommandCreateView.h"


CommandCreateView::CommandCreateView(DeviceContext::CommandGenerator::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateView::~CommandCreateView()
{

}


void CommandCreateView::CreateRTV(ID3D12Device8* device_,ID3D12Resource* resource_ ,const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
{
	device_->CreateRenderTargetView(resource_ , desc_, descriptorHandleCPU_);
}

void CommandCreateView::CreateUAV(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* counterResource_)
{
	device_->CreateUnorderedAccessView(resource_, nullptr, desc_, descriptorHandleCPU_);
}


void CommandCreateView::CreateSRV(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
{
	device_->CreateShaderResourceView(resource_, desc_, descriptorHandleCPU_);

}

void CommandCreateView::CreateDSV(ID3D12Device8* device_, ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
{
	device_->CreateDepthStencilView(resource_, desc_, descriptorHandleCPU_);

}
