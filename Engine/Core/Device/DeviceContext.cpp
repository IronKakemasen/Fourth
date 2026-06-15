#include "PreCompileHedder.h"
#include "DeviceContext.h"
#include "Commands/DeviceContextCommandBehavior.h"
#include "DeviceSetupper/DeviceContextSetupper.h"
#include "DeviceContextCommandProvider/DeviceContextCommandProvider.h"


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

	TakeOverCoreParts(instanceKey_);
	Logger::Log("Create: CoreParts", fileName);

	CreateCommandProvider(instanceKey_);
	Logger::Log("Create: CommandProvider", fileName);


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

UINT DeviceContext::CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_)
{
	return device->GetDescriptorHandleIncrementSize(type_);
}

