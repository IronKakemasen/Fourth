#include "PreCompileHedder.h"
#include "DeviceContextCommandProvider.h"
#include "../../../Resource/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../Resource/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"

#include "../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"



DeviceContext::CommandProvider::CommandProvider(DeviceContext::InstanceKey instanceKey_, 
	std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_,CommandMap* commandContainer_) : deviceGetter(func_), commandContainer(commandContainer_)
{
	
}


[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)> DeviceContext::CommandProvider::GetCreateConstantBufferCommmand()
{
	auto retFunc = [this](const ConstantBufferDescription& desc_)
	{
		auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
		auto& container = *commandContainer;

		CreatingGPUBuffer* command = static_cast<CreatingGPUBuffer*>(container[DeviceContext::CommandType::kCreatingGPU_Buffer][0].get());

		return command->CreateConstantBuffer(device, desc_);
	};

	return retFunc;
};

[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)> DeviceContext::CommandProvider::GetCreateColorBufferCommmand()
{
	auto retFunc = [this](const ColorBufferDescription& desc_)
	{
		auto* device = deviceGetter(DeviceContext::DeviceAccessKey{});
		auto& container = *commandContainer;

		CreatingGPUBuffer* command = static_cast<CreatingGPUBuffer*>(container[DeviceContext::CommandType::kCreatingGPU_Buffer][0].get());

		return command->CreateColorBuffer(device, desc_);
	};

	return retFunc;

}




