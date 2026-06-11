#include "PreCompileHedder.h"
#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"
#include "DescriptorHeapClass/DescriptorHeapClass.h"


//ビュー生成クラス達
#include "ViewCreator/RTV_Creator/RTV_Creator.h"
#include "ViewCreator/SRV_Creator/SRV_Creator.h"
#include "ViewCreator/DSV_Creator/DSV_Creator.h"
#include "ViewCreator/UAV_Creator/UAV_Creator.h"


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
	auto* rtvCreator = static_cast<ViewCreatorBehavior<D3D12_RENDER_TARGET_VIEW_DESC>*>(viewCreatorContainer[ViewType::kRTV].get());
	auto* srvCreator = static_cast<ViewCreatorBehavior<D3D12_SHADER_RESOURCE_VIEW_DESC>*>(viewCreatorContainer[ViewType::kSRV].get());
	auto* dsvCreator = static_cast<ViewCreatorBehavior<D3D12_DEPTH_STENCIL_VIEW_DESC>*>(viewCreatorContainer[ViewType::kDSV].get());
	auto* uavCreator = static_cast<ViewCreatorBehavior<D3D12_UNORDERED_ACCESS_VIEW_DESC>*>(viewCreatorContainer[ViewType::kUAV].get());

	rtvCreator->SetCommand(createRtv_);
	srvCreator->SetCommand(createSrv_);
	dsvCreator->SetCommand(createDsv_);

	uavCreator->SetCommand([createUav_](ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE handle_)
	{
		createUav_(resource_, desc_, handle_, nullptr);
	});
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
	viewCreatorContainer[ViewType::kRTV] =
		std::make_unique<RTV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_,&RTV_descriptorHandleCPUContainer);
	Logger::Log("Create: RTV_Creator ", fileName);

}

template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[ViewType::kSRV] =
		std::make_unique<SRV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_);
	Logger::Log("Create: SRV_Creator ", fileName);

	viewCreatorContainer[ViewType::kUAV] =
		std::make_unique<UAV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_);
	Logger::Log("Create: UAV_Creator ", fileName);

}


template <>
void DescriptorHeapContext::CreateViewCreator<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(DescriptorHeapClass* srcPtr_)
{
	viewCreatorContainer[ViewType::kDSV] =
		std::make_unique<DSV_Creator>(DescriptorHeapContext::CreateKey{}, srcPtr_, &DSV_descriptorHandleCPUContainer);
	Logger::Log("Create: DSV_Creator ", fileName);

}

template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(UINT, bool, UINT);
template void DescriptorHeapContext::CreateDescriptorHeap<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(UINT, bool, UINT);
