#include "DeviceContext.h"
#include "DeviceSetupper/DeviceContextSetupper.h"

//コマンド窓口
#include "DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"


namespace
{
	std::string const fileName = "DeviceContext.cpp";
}

DeviceContext::DeviceContext(DeviceContext::InstanceKey instanceKey_)
{
	Logger::Entry("DeviceContext::Constructor");

	TakeOverCoreParts(instanceKey_);
	CreateCommandProvider(instanceKey_);
	CreateCommandExecutor(instanceKey_);

	Logger::End("DeviceContext::Constructor");
}

DeviceContext::~DeviceContext()
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	Logger::Log("Create: CommandProvider", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::CreateCommandExecutor(DeviceContext::InstanceKey instanceKey_)
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::AccessKey key_) -> ID3D12Device8*
	{
		return device.Get();
	};

	commandExecutor.reset(new CommandExecutor(instanceKey_, deviceGetFunc));

	Logger::Log("Create: CommandExecutor", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_)
{
	//コアパーツの生成
	Setupper setupper(instanceKey_);

	std::tie(useAdapter, device, dxgiFactory) = setupper.HandOver(instanceKey_);
	Logger::Log("take over CoreParts", fileName);

}

