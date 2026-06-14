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

void DescriptorHeapContext::SetCreateDescroptorHeapCommand(DescroptorCreateCommand createDescriptor)
{
	descriptorHeapCreator->SetCommand(createDescriptor);
	Logger::Log("Set: DescroptorCreateCommand ", fileName);
}

void DescriptorHeapContext::SetCreateViewCommand
(
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
			CreateKey{},
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
