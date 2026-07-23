#include "DeviceContext.h"
#include "DeviceSetupper/DeviceContextSetupper.h"


#include "DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"
#include "DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"


namespace
{
	std::string const fileName = "DeviceContext.cpp";
}

DeviceContext::DeviceContext(NexusFieldProof proof_)
{
	Logger::Entry("DeviceContext::Constructor");

	TakeOverCoreParts(proof_);

	diplomat.reset
	(
		new DeviceContextDiplomat
		(
			proof_,
			std::move(InstantiateCommandProvider(proof_)),
			std::move(InstantiateCommandExecutor(proof_))
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
std::unique_ptr<DeviceContext::CommandProvider> DeviceContext::InstantiateCommandProvider(NexusFieldProof proof_)
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
	return std::make_unique<CommandProvider>(proof_, deviceGetFunc, dxgiFactoryGetter);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unique_ptr<DeviceContext::CommandExecutor> DeviceContext::InstantiateCommandExecutor(NexusFieldProof proof_)
{
	//デバイスにアクセスする関数オブジェ
	auto deviceGetFunc = [this](DeviceContext::AccessKey key_) -> ID3D12Device8*
	{
		return device.Get();
	};

	Logger::Log("Create: CommandExecutor", fileName);

	return std::make_unique<CommandExecutor>(proof_, deviceGetFunc);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceContext::TakeOverCoreParts(NexusFieldProof proof_)
{
	//コアパーツの生成
	Setupper setupper(proof_);

	std::tie(useAdapter, device, dxgiFactory) = setupper.HandOver(proof_);
	Logger::Log("take over CoreParts", fileName);

}

