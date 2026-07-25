#include "ViewCreator.h"

namespace 
{
	auto const fileName = "ViewCreator.cpp";
}


DescriptorHeapContext::ViewCreator::ViewCreator
(
	DescriptorHeapContext::NexusFieldProof proof_,
	DescriptorHeapPool* RTVdescriptorHeapPool_,
	DescriptorHeapPool* SRVUAVdescriptorHeapPool_,
	DescriptorHeapPool* DSVdescriptorHeapPool_,
	DescriptorHeapContext::CreateRTVCommand rtvCmd_,
	DescriptorHeapContext::CreateSRVCommand srvCmd_,
	DescriptorHeapContext::CreateDSVCommand dsvCmd_,
	DescriptorHeapContext::CreateUAVCommand uavCmd_
) :rtvCmd(rtvCmd_), srvCmd(srvCmd_), dsvCmd(dsvCmd_), uavCmd(uavCmd_)
{
	DescriptorHeapPool_Library.at(UINT(DescriptorHeapContext::ViewCreator::HeapType::kRTV))= RTVdescriptorHeapPool_;
	DescriptorHeapPool_Library.at(UINT(DescriptorHeapContext::ViewCreator::HeapType::kSRVUAV)) = SRVUAVdescriptorHeapPool_;
	DescriptorHeapPool_Library.at(UINT(DescriptorHeapContext::ViewCreator::HeapType::kDSV)) = DSVdescriptorHeapPool_;
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


