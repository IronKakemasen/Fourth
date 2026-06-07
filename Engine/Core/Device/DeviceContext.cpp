#include "PreCompileHedder.h"
#include "DeviceContext.h"
#include "Commands/DeviceContextCommandBehavior.h"
#include "DeviceSetupper/DeviceContextSetupper.h"
#include "DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "DeviceContextCommandGenerator/DeviceContextCommandGenerator.h"
#include "Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"
#include "Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"

DeviceContext::DeviceContext(DeviceContext::InstanceKey instanceKey_)
{
	Logger::Entry("DeviceContext::Constructor");

	TakeOverCoreParts(instanceKey_);
	Logger::Log("Create : CoreParts");

	CreateCommandGenerator(instanceKey_);
	Logger::Log("Create : CommandGenerator");

	CreateCommandProvider(instanceKey_);
	Logger::Log("Create : CommandProvider");

	CreateCommands(instanceKey_);
	Logger::Log("Create : Commands");


	Logger::End("DeviceContext::Constructor");
}

void DeviceContext::CreateCommands(DeviceContext::InstanceKey instanceKey_)
{
	commandContainer[CommandType::kCreateGPUBuffer].emplace_back(commandGenerator->CreateCommand<CommandCreateGPUBuffer>(instanceKey_));
	commandContainer[CommandType::kCreateDescriptorHeap].emplace_back(commandGenerator->CreateCommand<CommandCreateDescriptorHeap>(instanceKey_));

}

void DeviceContext::CreateCommandProvider(DeviceContext::InstanceKey instanceKey_)
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::DeviceAccessKey key_) -> ID3D12Device8*
	{
		return device.Get();
	};

	commandProvider.reset(new CommandProvider(instanceKey_, deviceGetFunc,&commandContainer));
}

void DeviceContext::CreateCommandGenerator(DeviceContext::InstanceKey instanceKey_)
{
	commandGenerator.reset(new CommandGenerator(instanceKey_));
}

void DeviceContext::TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_)
{
	//コアパーツの生成
	std::unique_ptr<Setupper> setupper = std::make_unique<DeviceContext::Setupper>(instanceKey_);

	device = setupper->HandOverDevice(instanceKey_);
	dxgiFactory = setupper->HandOverDxgiFactory(instanceKey_);
	useAdapter = setupper->HandOverAdapter(instanceKey_);
}

DeviceContext::~DeviceContext()
{

}


