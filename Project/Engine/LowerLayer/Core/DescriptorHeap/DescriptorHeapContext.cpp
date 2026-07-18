#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapPool/DescriptorHeapPool.h"
#include "ViewCreator/ViewCreator.h"
#include "DescriptorHeapToolLender/DescriptorHeapToolLender.h"

namespace
{
	std::string fileName = "DescriptorHeapContext.cpp";
}

using namespace ProjectConfig::Core;

DescriptorHeapContext::DescriptorHeapContext
(
	InstanceKey instanceKey_,
	CreateDescriptorHeapCommand createDescriptor_,
	CreateRTVCommand createRtv_,
	CreateSRVCommand createSrv_,
	CreateDSVCommand createDsv_,
	CreateUAVCommand createUav_,
	std::array<UINT, 3> incrementSizeOfDH_
)
{
	Logger::Entry("DescriptorHeapContext: Constructor");

	CreateDescriptorHeaps(instanceKey_, createDescriptor_,incrementSizeOfDH_.at(0), incrementSizeOfDH_.at(1), incrementSizeOfDH_.at(2));

	SetCreateViewCommand(instanceKey_, createRtv_, createSrv_, createDsv_, createUav_);

	toolLender.reset(new ToolLender(instanceKey_, viewCreator.get()));
	Logger::Log("Instantiate: ToolLender", fileName);


	Logger::End("DescriptorHeapContext: Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DescriptorHeapContext::CreateDescriptorHeaps
(
	InstanceKey instanceKey_,
	CreateDescriptorHeapCommand cmd_ ,
	UINT rtvDH_, 
	UINT srvDH_, 
	UINT dsvDH_
)
{

	DescriptorHeapCreator creator(instanceKey_, cmd_);
	Logger::Log("Instantiate: DescriptorHeapCreator", fileName);

	descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV] = 
		std::move(creator.Create<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(kNumDescriptorsRTVHeap, false, rtvDH_));
	Logger::Log("Create: DescriptorHeapRTV", fileName);

	descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV] =
		std::move(creator.Create<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(kNumDescriptorSRVHeap, true, srvDH_));
	Logger::Log("Create: DescriptorHeapSRV", fileName);

	descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV] =
		std::move(creator.Create<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(kNumDescriptorsDSVHeap, false, dsvDH_));
	Logger::Log("Create: DescriptorHeapDSV", fileName);


}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DescriptorHeapContext::SetCreateViewCommand
(
	InstanceKey key_,
	CreateRTVCommand createRtv_,
	CreateSRVCommand createSrv_,
	CreateDSVCommand createDsv_,
	CreateUAVCommand createUav_
)
{
	viewCreator.reset
	(
		new ViewCreator
		(
			key_,
			descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV].get(),
			descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV].get(),
			descriptorHeapContainer[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV].get(),
			std::move(createRtv_),
			std::move(createSrv_),
			std::move(createDsv_),
			std::move(createUav_)
		)
	);

	Logger::Log("Instantiate: ViewCreator", fileName);
	Logger::Log("Set: commandCreateView", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
