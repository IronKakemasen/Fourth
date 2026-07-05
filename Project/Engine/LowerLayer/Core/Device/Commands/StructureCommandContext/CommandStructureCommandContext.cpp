
#include "CommandStructureCommandContext.h"

namespace
{
	std::string fileName = "CommandStructureCommandContext.cpp";
}

CommandStructureCommandContext::CommandStructureCommandContext (DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandStructureCommandContext::~CommandStructureCommandContext ()
{

}

[[nodiscard]] Microsoft::WRL::ComPtr <ID3D12CommandQueue> CommandStructureCommandContext::CreateCommandQueue
(
	ID3D12Device* device_,
	D3D12_COMMAND_LIST_TYPE type_
)
{
	Microsoft::WRL::ComPtr <ID3D12CommandQueue> cmdQueue;
	
	D3D12_COMMAND_QUEUE_DESC desc{};

	desc.Type = type_;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	HRESULT hr = device_->CreateCommandQueue
	(
		&desc,
		IID_PPV_ARGS(cmdQueue.GetAddressOf())
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "CommandQueue生成失敗", fileName);
	Logger::Log("Create: CommandQueue", fileName);

	return cmdQueue;
}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandStructureCommandContext::CreateCommandAllocator
(
	ID3D12Device* device_,
	D3D12_COMMAND_LIST_TYPE type_
)
{
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;

	HRESULT hr = device_->CreateCommandAllocator
	(
		type_,
		IID_PPV_ARGS(cmdAllocator.GetAddressOf())
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "CommandAllocator生成失敗", fileName);
	Logger::Log("Create: CommandAllocator", fileName);

	return cmdAllocator;
}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> CommandStructureCommandContext::CreateCommandList
(
	ID3D12Device* device_,
	ID3D12CommandAllocator* cmdAllocator_,
	D3D12_COMMAND_LIST_TYPE type_
)
{
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList;

	HRESULT hr = device_->CreateCommandList
	(
		0,
		type_,
		cmdAllocator_,
		nullptr,
		IID_PPV_ARGS(cmdList.GetAddressOf())
	);

	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "CommandList生成失敗", fileName);
	Logger::Log("Create: CommandList", fileName);

	return cmdList;
}


