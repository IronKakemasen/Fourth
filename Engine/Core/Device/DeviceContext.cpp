#include "PreCompileHedder.h"
#include "DeviceContext.h"
#include "DeviceSetupper/DeviceContextSetupper.h"
#include "DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"
#include "DeviceContextCommandGenerator/DeviceContextCommandGenerator.h"

void DeviceContext::SetGPU_CreationCommands(GPUBufferCreator* gpuBufferCreator_)
{

}

DeviceContext::~DeviceContext()
{

}

DeviceContext::DeviceContext(DeviceContext::InstanceKey instanceKey_)
{
	TakeOverCoreParts(instanceKey_);
	CreateCommandExecutor();


}


void DeviceContext::CreateCommandExecutor()
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::DeviceAccessKey) -> ID3D12Device8*
	{
			return device.Get();
	};

	commandExecutor.reset(new CommandExecutor(CommandExecutor::InstanceKey{}, deviceGetFunc));
}

void DeviceContext::TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_)
{
	//コアパーツの生成
	std::unique_ptr<Setupper> setupper = std::make_unique<DeviceContext::Setupper>(instanceKey_);

	device = setupper->HandOverDevice(instanceKey_);
	dxgiFactory = setupper->HandOverDxgiFactory(instanceKey_);
	useAdapter = setupper->HandOverAdapter(instanceKey_);
}

