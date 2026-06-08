#include "PreCompileHedder.h"
#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapClass/DescriptorHeapClass.h"
#include "ViewCreator/RTV_Creator/RTV_Creator.h"
#include "ViewCreator/SRV_Creator/SRV_Creator.h"
#include "ViewCreator/DSV_Creator/DSV_Creator.h"

DescriptorHeapContext::DescriptorHeapContext(InstanceKey instanceKey_)
{
	Logger::Entry("DescriptorHeapContext::Constructor");

	descriptorHeapCreator.reset(new DescriptorHeapCreator(instanceKey_));
	Logger::Log("Instantiate : DescriptorHeapCreator");


	Logger::End("DescriptorHeapContext::Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}

void DescriptorHeapContext::SetCommand(DescroptorCreateCommand createFunc_)
{
	descriptorHeapCreator->SetCommand(createFunc_);
}

template<D3D12_DESCRIPTOR_HEAP_TYPE HeapType>
void DescriptorHeapContext::CreateDescriptorHeap(UINT numDescriptors_, bool shaderVisible_, UINT handleIncSize_)
{
	descriptorHeapContainer[HeapType] = std::make_unique<DescriptorHeapClass>(
		std::move(descriptorHeapCreator->createFunc(HeapType, numDescriptors_, shaderVisible_)),
		handleIncSize_,
		numDescriptors_
	);

	CreateViewCreator<HeapType>(descriptorHeapContainer[HeapType].get());
}


template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[kRTV] =
		std::make_unique<RTV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_);
}

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[kSRV] =
		std::make_unique<SRV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_);
}

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[kDSV] =
		std::make_unique<DSV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_);
}

template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(UINT, bool, UINT);
