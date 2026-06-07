#include "PreCompileHedder.h"
#include "DeviceContextCommandProvider.h"
#include "../../../Resource/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../Resource/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"

#include "../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"
#include "../Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"



DeviceContext::CommandProvider::CommandProvider(DeviceContext::InstanceKey instanceKey_, 
	std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_,CommandMap* commandContainer_) : deviceGetter(func_), commandContainer(commandContainer_)
{
	
}

[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> DeviceContext::CommandProvider::PassCreateDescriptorHeapCommand()
{
	auto retFunc = [this](D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible_)
	{
		auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
		auto& container = *commandContainer;
		auto* command = static_cast<CommandCreateDescriptorHeap*>(container[DeviceContext::CommandType::kCreateDescriptorHeap][0].get());

		return command->Create(device, heapType_,numDescriptors_, shaderVisible_);
	};

	return retFunc;

}


template <>
[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)> DeviceContext::CommandProvider::PassCreateBufferCommand()
{
	auto retFunc = [this](const ConstantBufferDescription& desc_)
		{
			auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
			auto& container = *commandContainer;

			CommandCreateGPUBuffer* command = static_cast<CommandCreateGPUBuffer*>(container[DeviceContext::CommandType::kCreateGPUBuffer][0].get());

			return command->CreateConstantBuffer(device, desc_);
		};

	return retFunc;

}

template <>
[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)> DeviceContext::CommandProvider::PassCreateBufferCommand()
{
	auto retFunc = [this](const ColorBufferDescription& desc_)
		{
			auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
			auto& container = *commandContainer;

			CommandCreateGPUBuffer* command = static_cast<CommandCreateGPUBuffer*>(container[DeviceContext::CommandType::kCreateGPUBuffer][0].get());

			return command->CreateColorBuffer(device, desc_);
		};

	return retFunc;
}






