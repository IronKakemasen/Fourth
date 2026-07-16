
#include "DeviceContextCommandExecutor.h"
#include "../Commands/DeviceContextCommandBehavior.h"

//コマンド群
#include "../Commands/StructureCommandContext/CommandStructureCommandContext.h"
#include "../Commands/CreateFenceObject/CommandCreateFenceObject.h"


using namespace  ProjectConfig::Render;

using CommandContextCorePartsRuntime =
std::tuple
<
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>,
	std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer>,
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>
>;

using CommandContextCorePartsUpload =
std::tuple<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>>;


namespace
{
	auto fileName = "DeviceContextCommandExecutor.cpp";
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceContext::CommandExecutor::CommandExecutor
(
	DeviceContext::InstanceKey instanceKey_,
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_
) :deviceGetter(deviceGetter_)
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT DeviceContext::CommandExecutor::CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_)
{
	auto* device = deviceGetter(DeviceContext::AccessKey{});

	return device->GetDescriptorHandleIncrementSize(type_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Fence> DeviceContext::CommandExecutor::CreateFence()
{
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	auto* device = deviceGetter(DeviceContext::AccessKey{});

	CommandCreateFenceObject command(DeviceContext::GenerateKey{});
	fence = std::move(command.CreateFenceObj(device));

	return fence;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] CommandContextCorePartsRuntime
DeviceContext::CommandExecutor::CreateCommandContextCorePartsForRuntime(DeviceContext::InstanceKey instanceKey_)
{
	//ランタイム用なので万能型
	auto const cmdListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

	//コアパーツ生成ツール
	CommandStructureCommandContext tool(DeviceContext::GenerateKey{});
	auto* device = deviceGetter(DeviceContext::AccessKey{});

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
	std::array < Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)NumBuffer::kDoubleBuffer > cmdAllocators;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList;

	//生成
	{
		cmdQueue = tool.CreateCommandQueue(device, cmdListType);

		for (int i = 0;i < (UINT)NumBuffer::kDoubleBuffer;++i)
		{
			cmdAllocators.at(i) = tool.CreateCommandAllocator(device, cmdListType);
		}

		cmdList = tool.CreateCommandList(device, cmdAllocators.at(0).Get(), cmdListType);
	}

	return std::make_tuple(cmdQueue, cmdAllocators, cmdList);
}

[[nodiscard]] CommandContextCorePartsUpload
DeviceContext::CommandExecutor::CreateCommandContextCorePartsForUpload(DeviceContext::InstanceKey instanceKey_)
{
	//コマンドリストのタイプはアップロードしかしないのでコピーだけでいい
	auto const cmdListType = D3D12_COMMAND_LIST_TYPE_COPY;

	//コアパーツ生成ツール
	CommandStructureCommandContext tool(DeviceContext::GenerateKey{});
	auto* device = deviceGetter(DeviceContext::AccessKey{});

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> cmdList;

	//生成
	{
		cmdAllocator = tool.CreateCommandAllocator(device, cmdListType);
		cmdList = tool.CreateCommandList(device, cmdAllocator.Get(), cmdListType);
	}

	return std::make_tuple(cmdAllocator, cmdList);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
