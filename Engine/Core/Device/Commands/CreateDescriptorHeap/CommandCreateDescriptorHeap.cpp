#include "PreCompileHedder.h"
#include "CommandCreateDescriptorHeap.h"


CommandCreateDescriptorHeap::CommandCreateDescriptorHeap(DeviceContext::CommandProvider::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateDescriptorHeap::~CommandCreateDescriptorHeap()
{

}


Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CommandCreateDescriptorHeap::Create(ID3D12Device8* device_, D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible)
{
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> ret_descriptorHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorheapDesc{};

	descriptorheapDesc.NodeMask = 0;
	descriptorheapDesc.Type = heapType_;
	descriptorheapDesc.NumDescriptors = numDescriptors_;
	descriptorheapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	HRESULT hr = device_->CreateDescriptorHeap(&descriptorheapDesc,
		IID_PPV_ARGS(ret_descriptorHeap.GetAddressOf()));

	assert(SUCCEEDED(hr));

	return ret_descriptorHeap;
}

