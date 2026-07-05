
#include "CommandOfCreatingGPUBuffer.h"
 


CommandCreateGPUResource::CommandCreateGPUResource(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateGPUResource::~CommandCreateGPUResource()
{

}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CommandCreateGPUResource::CreateResource
(
	ID3D12Device8* device_,
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValue_,
	D3D12_RESOURCE_STATES initialState_,
	const std::string& name_
)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> resource;

	//[ 生成 ]
	[[maybe_unused]] HRESULT hr = device_->CreateCommittedResource(
		&heapProperties_,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc_,
		initialState_,
		clearValue_,
		IID_PPV_ARGS(&resource));

	ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), name_ + ": リソース生成失敗", "CommandOfCreatingGPUBuffer.cpp");

	return resource;
}
