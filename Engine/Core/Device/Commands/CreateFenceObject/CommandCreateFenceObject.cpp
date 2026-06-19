#include "PreCompileHeader.h"
#include "CommandCreateFenceObject.h"

CommandCreateFenceObject::CommandCreateFenceObject(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateFenceObject::~CommandCreateFenceObject()
{

}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Fence> CommandCreateFenceObject::CreateFenceObj(ID3D12Device8* device_)
{
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	HRESULT hr = device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "フェンスの生成失敗", "CommandCreateFenceObject.cpp");

	return fence;
}

