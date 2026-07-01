#include "PreCompileHeader.h"
#include "CommandCreateRootSignature.h"


namespace
{
	auto fileName = "CommandCreateRootSignature.cpp";
}

CommandCreateRootSignature::CommandCreateRootSignature(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreateRootSignature::~CommandCreateRootSignature()
{

}


void CommandCreateRootSignature::CreateRootSignature
(
	ID3D12Device8* device_,
	UINT nodeMask_,
	Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_,
	ID3D12RootSignature** doublePtr_rootSignature_
)
{
	HRESULT hr = device_->CreateRootSignature
	(
		nodeMask_,
		signatureBlob_->GetBufferPointer(),
		signatureBlob_->GetBufferSize(),
		IID_PPV_ARGS(doublePtr_rootSignature_)
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "RootSignatureの生成失敗", fileName);
	Logger::Log("Create: rootSignature", fileName);
}
