#include "PreCompileHedder.h"
#include "DeviceContext.h"
#include "Commands/DeviceContextCommandBehavior.h"
#include "DeviceSetupper/DeviceContextSetupper.h"
#include "DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "DeviceContextCommandGenerator/DeviceContextCommandGenerator.h"


std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)>DeviceContext::GetGetCreateConstantBufferCommand()
{
	return commandProvider->GetCreateConstantBufferCommmand();
}

std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)>DeviceContext::GetGetCreateColorBufferCommand()
{
	return commandProvider->GetCreateColorBufferCommmand();
}


DeviceContext::DeviceContext(DeviceContext::InstanceKey instanceKey_)
{
	//コアパーツの生成
	TakeOverCoreParts(instanceKey_);
	//コマンド生成クラスのインスタンス化
	CreateCommandGenerator(instanceKey_);
	//コマンド実行クラスのインスタンス化
	CreateCommandExecutor(instanceKey_);
	//コマンド生成
	CreateCommands(instanceKey_);

}

void DeviceContext::CreateCommands(DeviceContext::InstanceKey instanceKey_)
{
	auto generate = [this, instanceKey_](CommandType type_)
	{
		commandContainer[type_].emplace_back(commandGenerator->CreateCommand(instanceKey_, type_));
	};

	generate(CommandType::kCreatingGPU_Buffer);

}

void DeviceContext::CreateCommandExecutor(DeviceContext::InstanceKey instanceKey_)
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


