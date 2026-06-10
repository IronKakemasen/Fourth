#include "PreCompileHedder.h"
#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapClass/DescriptorHeapClass.h"
#include "ViewCreator/RTV_Creator/RTV_Creator.h"
#include "ViewCreator/SRV_UAV_Creator/SRV_UAV_Creator.h"
#include "ViewCreator/DSV_Creator/DSV_Creator.h"

namespace
{
	std::string fileName = "DescriptorHeapContext.cpp";
}

DescriptorHeapContext::DescriptorHeapContext(InstanceKey instanceKey_)
{
	Logger::Entry("DescriptorHeapContext: Constructor");

	descriptorHeapCreator.reset(new DescriptorHeapCreator(instanceKey_));
	Logger::Log("Instantiate: DescriptorHeapCreator", fileName);


	Logger::End("DescriptorHeapContext: Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}

void DescriptorHeapContext::SetCommand
(
	DescroptorCreateCommand createFunc_,
	CreateRTVCommand rtvCreate_,
	CreateSRVCommand srvCreate_,
	CreateDSVCommand dsvCreate_
)
{
	descriptorHeapCreator->SetCommand(createFunc_);
	Logger::Log("Set: DescroptorCreateCommand ", fileName);


}

template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
void DescriptorHeapContext::CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_)
{
	descriptorHeapContainer[HeapType] = std::make_unique<DescriptorHeapClass>
	(
		std::move(descriptorHeapCreator->createFunc(HeapType, numDescriptors_, shaderVisible_)),
		handleIncSize_,
		numDescriptors_,
		GetDescriptorName(HeapType)
	);

	CreateViewCreator<HeapType>(descriptorHeapContainer[HeapType].get());
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

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[kRTV] =
		std::make_unique<RTV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_,&RTV_descriptorHandleCPUContainer);
	Logger::Log("Create: RTV_Creator ", fileName);

}

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[kSRV_UAV] =
		std::make_unique<SRV_UAV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_);
	Logger::Log("Create: SRV_UAV_Creator ", fileName);

}

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[kDSV] =
		std::make_unique<DSV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_, &DSV_descriptorHandleCPUContainer);
	Logger::Log("Create: DSV_Creator ", fileName);

}

template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(UINT, bool, UINT);
