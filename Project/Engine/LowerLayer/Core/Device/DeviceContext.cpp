#include "DeviceContext.h"
#include "DeviceSetupper/DeviceContextSetupper.h"


#include "DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"
#include "DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"


namespace
{
	std::string const fileName = "DeviceContext.cpp";
}

DeviceContext::DeviceContext(DeviceContext::InstanceKey instanceKey_)
{
	Logger::Entry("DeviceContext::Constructor");

	TakeOverCoreParts(instanceKey_);

	diplomat.reset
	(
		new DeviceContextDiplomat
		(
			instanceKey_,
			std::move(InstantiateCommandProvider(instanceKey_)),
			std::move(InstantiateCommandExecutor(instanceKey_))
		)
	);

	Logger::End("DeviceContext::Constructor");
}

DeviceContext::~DeviceContext()
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unique_ptr<DeviceContext::CommandProvider> DeviceContext::InstantiateCommandProvider(DeviceContext::InstanceKey instanceKey_)
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

	Logger::Log("Create: CommandProvider", fileName);
	return std::make_unique<CommandProvider>(instanceKey_, deviceGetFunc, dxgiFactoryGetter);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unique_ptr<DeviceContext::CommandExecutor> DeviceContext::InstantiateCommandExecutor(DeviceContext::InstanceKey instanceKey_)
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::AccessKey key_) -> ID3D12Device8*
	{
		return device.Get();
	};

	Logger::Log("Create: CommandExecutor", fileName);

	return std::make_unique<CommandExecutor>(instanceKey_, deviceGetFunc);
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

