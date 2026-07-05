#include "PreCompileHeader.h"
#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapPool/DescriptorHeapPool.h"
#include "ViewCreator/ViewCreator.h"

namespace
{
	std::string fileName = "DescriptorHeapContext.cpp";
}

DescriptorHeapContext::DescriptorHeapContext
(
	InstanceKey instanceKey_,
	DescriptorCreateCommand createDescriptor_,
	CreateRTVCommand createRtv_,
	CreateSRVCommand createSrv_,
	CreateDSVCommand createDsv_,
	CreateUAVCommand createUav_,
	std::array<UINT, 3> incrementSizeOfDH_
)
{
	Logger::Entry("DescriptorHeapContext: Constructor");


	descriptorHeapCreator.reset(new DescriptorHeapCreator(instanceKey_));
	Logger::Log("Instantiate: DescriptorHeapCreator", fileName);

	descriptorHeapCreator->SetCommand(createDescriptor_);
	Logger::Log("Set: commandCreateDescriptor", fileName);

	CreateDescriptorHeaps(incrementSizeOfDH_.at(0), incrementSizeOfDH_.at(1), incrementSizeOfDH_.at(2));
	Logger::Log("Create: DescriptorHeaps", fileName);

	SetCreateViewCommand(instanceKey_, createRtv_, createSrv_, createDsv_, createUav_);
	Logger::Log("Set: commandCreateView", fileName);


	Logger::End("DescriptorHeapContext: Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ViewCreator* DescriptorHeapContext::GetViewCreator(ViewCreatorGetKey key_)
{
	return viewCreator.get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DescriptorHeapContext::CreateDescriptorHeaps(UINT rtvDH_, UINT srvDH_, UINT dsvDH_)
{
	using namespace ProjectConfig::Core;

	//RTV
	CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(kNumDescriptorsRTVHeap, false, rtvDH_);
	//SRV/UAV
	CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(kNumDescriptorSRVHeap, true, srvDH_);
	//DSV
	CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(kNumDescriptorsDSVHeap, false, dsvDH_);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DescriptorHeapContext::SetCreateDescriptorHeapCommand(DescriptorCreateCommand createDescriptor)
{
	descriptorHeapCreator->SetCommand(createDescriptor);
	Logger::Log("Set: DescriptorCreateCommand ", fileName);
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

	Logger::Log("Create: ViewCreator", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
void DescriptorHeapContext::CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_)
{
	descriptorHeapContainer[HeapType] = std::make_unique<DescriptorHeapPool>
	(
		std::move(descriptorHeapCreator->createFunc(HeapType, numDescriptors_, shaderVisible_)),
		handleIncSize_,
		numDescriptors_,
		shaderVisible_,
		GetDescriptorName(HeapType)
	);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string DescriptorHeapContext::GetDescriptorName(D3D12_DESCRIPTOR_HEAP_TYPE heapType_)
{
	ErrorMessageOutput::Assert::DetectError((heapType_ < D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES), "TypeError: 要素外アクセス", fileName);

	std::string descriptorHeap = "_descriptorHeap";

	static const std::string nameTable[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES + 1] =
	{
		"SRV_UAV",
		"Sampler",
		"RTV",
		"DSV",
		"dummy" //このケースは上で止めてます
	};

	return nameTable[heapType_] + descriptorHeap;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(UINT, bool, UINT);
