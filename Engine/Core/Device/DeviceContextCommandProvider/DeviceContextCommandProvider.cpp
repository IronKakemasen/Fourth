#include "PreCompileHedder.h"
#include "DeviceContextCommandProvider.h"

#include "../../../Resource/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../Resource/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"
#include "../../../Resource/BufferDescriptions/SRV_UAVBufferDescription/SRV_UAVBufferDescription.h"

#include "../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"
#include "../Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"
#include "../Commands/CreateView/CommandCreateView.h"



DeviceContext::CommandProvider::CommandProvider(DeviceContext::InstanceKey instanceKey_, 
	std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_,CommandMap* commandContainer_) : deviceGetter(func_), commandContainer(commandContainer_)
{
	
}


//CreateViewCommand
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
[[nodiscard]] std::function<void(ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>
DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_RENDER_TARGET_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
		auto& container = *commandContainer;
		auto* command = static_cast<CommandCreateView*>(container[DeviceContext::CommandType::kCreateResourceView][0].get());

		return command->CreateRTV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}
template<>
[[nodiscard]] std::function<void(ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>
DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_SHADER_RESOURCE_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
		auto& container = *commandContainer;
		auto* command = static_cast<CommandCreateView*>(container[DeviceContext::CommandType::kCreateResourceView][0].get());

		return command->CreateSRV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}

template<>
[[nodiscard]] std::function<void(ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>
DeviceContext::CommandProvider::ProvideCreateViewCommand()
{
	auto retFunc = [this](ID3D12Resource* resource_, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)
	{
		auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
		auto& container = *commandContainer;
		auto* command = static_cast<CommandCreateView*>(container[DeviceContext::CommandType::kCreateResourceView][0].get());

		return command->CreateDSV(device, resource_, desc_, descriptorHandleCPU_);
	};

	return retFunc;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






//CreateDescriptorHeapCommand
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)>
DeviceContext::CommandProvider::ProvideCreateDescriptorHeapCommand()
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






//CreateBufferCommand
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)>
DeviceContext::CommandProvider::ProvideCreateBufferCommand()
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
[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)> DeviceContext::CommandProvider::ProvideCreateBufferCommand()
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

template <>
[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const SRV_UAVBufferDescription&)> DeviceContext::CommandProvider::ProvideCreateBufferCommand()
{
	auto retFunc = [this](const SRV_UAVBufferDescription& desc_)
		{
			auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
			auto& container = *commandContainer;

			CommandCreateGPUBuffer* command = static_cast<CommandCreateGPUBuffer*>(container[DeviceContext::CommandType::kCreateGPUBuffer][0].get());

			return command->CreateSRV_UAVBuffer(device, desc_);
		};

	return retFunc;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






