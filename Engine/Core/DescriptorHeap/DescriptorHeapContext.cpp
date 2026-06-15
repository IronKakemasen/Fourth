#include "PreCompileHedder.h"
#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapClass/DescriptorHeapClass.h"
#include "ViewCreator/ViewCreator.h"


//ビュー生成クラス達

namespace
{
	std::string fileName = "DescriptorHeapContext.cpp";
}

DescriptorHeapContext::DescriptorHeapContext
(
	InstanceKey instanceKey_,
	DescroptorCreateCommand createDescriptor_,
	CreateRTVCommand createRtv_,
	CreateSRVCommand createSrv_,
	CreateDSVCommand createDsv_,
	CreateUAVCommand createUav_,
	UINT incrementSizeOfDH_[3]
)
{
	Logger::Entry("DescriptorHeapContext: Constructor");

	descriptorHeapCreator.reset(new DescriptorHeapCreator(instanceKey_));
	Logger::Log("Create: DescriptorHeapCreator", fileName);
	
	descriptorHeapCreator->SetCommand(createDescriptor_);
	Logger::Log("Set: commandCreateDescriptor", fileName);

	CreateDescriptorHeaps(incrementSizeOfDH_[0], incrementSizeOfDH_[1], incrementSizeOfDH_[2]);
	Logger::Log("Create: DescriptorHeaps", fileName);

	SetCreateViewCommand(instanceKey_, createRtv_, createSrv_, createDsv_, createUav_);
	Logger::Log("Set: commandCreateView", fileName);


	Logger::End("DescriptorHeapContext: Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}

ViewCreator* DescriptorHeapContext::ShareViewCreator(ViewCreatorShareKey key_)
{
	return viewCreator.get();
}

void DescriptorHeapContext::CreateDescriptorHeaps(UINT rtvDH_, UINT srvDH_, UINT dsvDH_)
{
	using namespace ProjectConfig::Core;

	//RTV
	CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(kNumDescriptorsRTVHeap, false, rtvDH_);
	//SRV
	CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(kNumDescriptorSRVHeap, false, srvDH_);
	//DSV
	CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(kNumDescriptorsDSVHeap, false, dsvDH_);

}

void DescriptorHeapContext::SetCreateDescroptorHeapCommand(DescroptorCreateCommand createDescriptor)
{
	descriptorHeapCreator->SetCommand(createDescriptor);
	Logger::Log("Set: DescroptorCreateCommand ", fileName);
}

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


template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
void DescriptorHeapContext::CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_)
{
	descriptorHeapContainer[HeapType] = std::make_unique<DescriptorHeapClass>
	(
		std::move(descriptorHeapCreator->createFunc(HeapType, numDescriptors_, shaderVisible_)),
		handleIncSize_,
		numDescriptors_,
		shaderVisible_,
		GetDescriptorName(HeapType)
	);

}


std::string DescriptorHeapContext::GetDescriptorName(D3D12_DESCRIPTOR_HEAP_TYPE heapType_)
{
	std::string descriptorHeap = "_descriptorHeap";

	std::string nameTable[D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES] =
	{
		"SRV_UAV",
		"Sampler",
		"RTV",
		"DSV"
	};

	return nameTable[heapType_] + descriptorHeap;
}

template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(UINT, bool, UINT);
