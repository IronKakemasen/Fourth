#include "PreCompileHeader.h"
#include "CommandContext.h"

CommandContext::CommandContext
(
	InstanceKey instanceKey_,
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_,
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, ProjectConfig::Render::kRequiredGPUBufferSum> commandAllocators_,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList_
) :commandQueue(std::move(commandQueue_)), commandAllocators(std::move(commandAllocators_)), commandList(std::move(commandList_))
{

}

ID3D12CommandQueue* CommandContext::GetCommandQueue(CmdQueueGetKey getKey_)
{
	return commandQueue.Get();
}