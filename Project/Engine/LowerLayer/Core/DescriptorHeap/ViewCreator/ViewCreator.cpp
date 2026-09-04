#include "ViewCreator.h"

//外部
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCmdLicences.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"

namespace 
{
	auto const fileName = "ViewCreator.cpp";
}


DescriptorHeapContext::ViewCreator::ViewCreator
(
	DescriptorHeapContext::NexusFieldProof proof_,
	DescriptorHeapPoolContainer& descriptorHeapPoolContainer_,
	DeviceContextDiplomat& deviceContextDiplomat_
)
{
	//deviceContextからビュー生成のコマンドを渡してももらう
	auto* deviceContextCmdProvider = deviceContextDiplomat_.Access<DeviceContext::CommandProvider>();
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC>> licenceRTV;
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC>> licenceSRV;
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC>> licenceDSV;
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateUAV> licenceUAV;

	rtvCmd = deviceContextCmdProvider->Provide<DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC>>(licenceRTV);
	srvCmd = deviceContextCmdProvider->Provide<DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC>>(licenceSRV);
	dsvCmd = deviceContextCmdProvider->Provide<DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC>>(licenceDSV);
	uavCmd = deviceContextCmdProvider->Provide<DeviceContextCmds::CreateUAV>(licenceUAV);
	

	//取り出し識別子が異なるので移し替える
	descriptorHeapPoolArray.at(UINT(DescriptorHeapContext::ViewCreator::HeapType::kRTV)) =
		descriptorHeapPoolContainer_.Export<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(proof_);

	descriptorHeapPoolArray.at(UINT(DescriptorHeapContext::ViewCreator::HeapType::kSRVUAV)) =
		descriptorHeapPoolContainer_.Export<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(proof_);

	descriptorHeapPoolArray.at(UINT(DescriptorHeapContext::ViewCreator::HeapType::kDSV)) =
		descriptorHeapPoolContainer_.Export<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(proof_);

	Logger::Log("Set: commandCreateView", fileName);

}


template<>
void DescriptorHeapContext::ViewCreator::Log<DescriptorHeapContext::ViewCreator::HeapType::kRTV>
(const uint32_t handle_)const
{
	Logger::Log("Dispatched < RTV > [ " + std::to_string(handle_) + " ]", fileName);
}

template<>
void DescriptorHeapContext::ViewCreator::Log<DescriptorHeapContext::ViewCreator::HeapType::kSRVUAV>
(const uint32_t handle_)const
{
	Logger::Log("Dispatched < SRVUAV > [ " + std::to_string(handle_) + " ]", fileName);
}

template<>
void DescriptorHeapContext::ViewCreator::Log<DescriptorHeapContext::ViewCreator::HeapType::kDSV>
(const uint32_t handle_)const
{
	Logger::Log("Dispatched < DSV > [ " + std::to_string(handle_) + " ]", fileName);
}


template
void DescriptorHeapContext::ViewCreator::Log<DescriptorHeapContext::ViewCreator::HeapType::kRTV>
(const uint32_t handle_)const;

template
void DescriptorHeapContext::ViewCreator::Log<DescriptorHeapContext::ViewCreator::HeapType::kSRVUAV>
(const uint32_t handle_)const;

template
void DescriptorHeapContext::ViewCreator::Log<DescriptorHeapContext::ViewCreator::HeapType::kDSV>
(const uint32_t handle_)const;


