#include "PreCompileHeader.h"
#include "DeviceContext.h"
#include "Commands/DeviceContextCommandBehavior.h"
#include "DeviceSetupper/DeviceContextSetupper.h"
#include "DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"


//コマンド
#include "Commands/CreateDescriptorHeap/CommandCreateDescriptorHeap.h"
#include "Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"
#include "Commands/CreateView/CommandCreateView.h"


namespace
{
	std::string const fileName = "DeviceContext.cpp";
}

DeviceContext::DeviceContext(DeviceContext::InstanceKey instanceKey_)
{
	Logger::Entry("DeviceContext::Constructor");

	{
		TakeOverCoreParts(instanceKey_);
		Logger::Log("Create: CoreParts", fileName);
	}

	{
		CreateCommandProvider(instanceKey_);
		Logger::Log("Create: CommandProvider", fileName);
	}

	{
		CreateCommandExecutor(instanceKey_);
		Logger::Log("Create: CommandExecutor", fileName);
	}


	Logger::End("DeviceContext::Constructor");
}

void DeviceContext::CreateCommandProvider(DeviceContext::InstanceKey instanceKey_)
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::AccessKey key_) -> ID3D12Device8*
	{
		return device.Get();
	};

	//dxgiFactoryにアクセスする関数オブジェ
	auto dxgiFactoryGetter = [this](DeviceContext::AccessKey key_) -> IDXGIFactory7*
	{
		return dxgiFactory.Get();
	};

	commandProvider.reset(new CommandProvider(instanceKey_, deviceGetFunc, dxgiFactoryGetter));
}

void DeviceContext::CreateCommandExecutor(DeviceContext::InstanceKey instanceKey_)
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::AccessKey key_) -> ID3D12Device8*
	{
		return device.Get();
	};

	commandExecutor.reset(new CommandExecutor(instanceKey_, deviceGetFunc));
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
