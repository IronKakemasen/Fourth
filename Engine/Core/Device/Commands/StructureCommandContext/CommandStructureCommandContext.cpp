#include "PreCompileHeader.h"
#include "CommandStructureCommandContext.h"

namespace
{
	std::string fileName = "CommandStructureCommandContext .cpp";
}

CommandStructureCommandContext::CommandStructureCommandContext (DeviceContext::CommandProvider::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandStructureCommandContext::~CommandStructureCommandContext ()
{

}

[[nodiscard]] Microsoft::WRL::ComPtr <ID3D12CommandQueue> CommandStructureCommandContext::CreateCommandQueue(ID3D12Device* device_)
{
	Microsoft::WRL::ComPtr <ID3D12CommandQueue> cmdQueue;
	
	D3D12_COMMAND_QUEUE_DESC desc{};

	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	HRESULT hr = device_->CreateCommandQueue
	(
		&desc,
		IID_PPV_ARGS(cmdQueue.GetAddressOf())
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "Create: CommandQueue", fileName);

	return cmdQueue;
}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandStructureCommandContext::CreateCommandAllocator(ID3D12Device* device_)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;

	HRESULT hr = device_->CreateCommandAllocator
	(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(cmdAllocator.GetAddressOf())
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "Create: CommandAllocator", fileName);

	return cmdAllocator;
}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> CommandStructureCommandContext::CreateCommandList
(
	ID3D12Device* device_,
	ID3D12CommandAllocator* cmdAllocator_
)
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList;

	HRESULT hr = device_->CreateCommandList
	(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator_,
		nullptr,
		IID_PPV_ARGS(cmdList.GetAddressOf())
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "Create: CommandList", fileName);

	return cmdList;
}


