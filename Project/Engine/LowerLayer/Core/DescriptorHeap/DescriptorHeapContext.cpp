#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapPool/DescriptorHeapPool.h"
#include "ViewCreator/ViewCreator.h"
#include "DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLender.h"
#include "DescriptorHeapContextDiplomat/DescriptorHeapContextDiplomat.h"

//外部
#include "../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"

namespace
{
	std::string fileName = "DescriptorHeapContext.cpp";
}

using namespace ProjectConfig::Core;

DescriptorHeapContext::DescriptorHeapContext
(
	DescriptorHeapContext::NexusFieldProof proof_,
	DeviceContextDiplomat* deviceContextDiplomat_
)
{
	Logger::Entry("DescriptorHeapContext: Constructor");

	
	//各種DescriptorHeapを生成する
	CreateDescriptorHeaps(proof_, deviceContextDiplomat_);
	//ViewCreatorを生成して、中にview生成コマンドを積む
	SetCreateViewCommand(proof_, deviceContextDiplomat_);

	diplomat.reset
	(
		new DescriptorHeapContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, viewCreator.get())
		)
	);
	Logger::Log("Instantiate: ToolLender", fileName);
	Logger::Log("Instantiate: DescriptorHeapContextDiplomat", fileName);


	Logger::End("DescriptorHeapContext: Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DescriptorHeapContext::CreateDescriptorHeaps(DescriptorHeapContext::NexusFieldProof proof_, DeviceContextDiplomat* deviceContextDiplomat_)
{
	auto* cmdExecutor = deviceContextDiplomat_->Access<DeviceContext::CommandExecutor>();
	auto* cmdProvider = deviceContextDiplomat_->Access<DeviceContext::CommandProvider>();

	auto createDescriptorHeapCmd = cmdProvider->ProvideCreateDescriptorHeapCommand();

	UINT rtvDHIncrementSIze = cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	UINT srvDHIncrementSIze = cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	UINT dsvDHIncrementSIze = cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	DescriptorHeapCreator creator(proof_, createDescriptorHeapCmd);
	Logger::Log("Instantiate: DescriptorHeapCreator", fileName);

	descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV] = 
		std::move(creator.Create<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(kNumDescriptorsRTVHeap, false, rtvDHIncrementSIze));
	
	Logger::Log("Create: DescriptorHeapRTV", fileName);

	descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV] =
		std::move(creator.Create<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(kNumDescriptorSRVHeap, true, srvDHIncrementSIze));
	Logger::Log("Create: DescriptorHeapSRV", fileName);

	descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV] =
		std::move(creator.Create<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(kNumDescriptorsDSVHeap, false, dsvDHIncrementSIze));
	Logger::Log("Create: DescriptorHeapDSV", fileName);


}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DescriptorHeapContext::SetCreateViewCommand
(
	NexusFieldProof proof_,
	DeviceContextDiplomat* deviceContextDiplomat_
)
{
	auto* cmdProvider = deviceContextDiplomat_->Access<DeviceContext::CommandProvider>();

	viewCreator.reset
	(
		new ViewCreator
		(
			proof_,
			descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV].get(),
			descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV].get(),
			descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV].get(),
			std::move(cmdProvider->ProvideCreateViewCommand<D3D12_RENDER_TARGET_VIEW_DESC>()),
			std::move(cmdProvider->ProvideCreateViewCommand<D3D12_SHADER_RESOURCE_VIEW_DESC>()),
			std::move(cmdProvider->ProvideCreateViewCommand<D3D12_DEPTH_STENCIL_VIEW_DESC>()),
			std::move(cmdProvider->ProvideCreateUAVCommand())
		)
	);

	Logger::Log("Instantiate: ViewCreator", fileName);
	Logger::Log("Set: commandCreateView", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
