
#include "ViewCreator.h"


DescriptorHeapContext::ViewCreator::ViewCreator
(
	DescriptorHeapContext::InstanceKey instanceKey_,
	DescriptorHeapPool* RTVdescriptorHeapPool_,
	DescriptorHeapPool* SRVUAVdescriptorHeapPool_,
	DescriptorHeapPool* DSVdescriptorHeapPool_,
	DescriptorHeapContext::CreateRTVCommand rtvCmd_,
	DescriptorHeapContext::CreateSRVCommand srvCmd_,
	DescriptorHeapContext::CreateDSVCommand dsvCmd_,
	DescriptorHeapContext::CreateUAVCommand uavCmd_
) :rtvCmd(rtvCmd_), srvCmd(srvCmd_), dsvCmd(dsvCmd_), uavCmd(uavCmd_)
{
	DescriptorHeapPool_Library[kRTV] = RTVdescriptorHeapPool_;
	DescriptorHeapPool_Library[kSRVUAV] = SRVUAVdescriptorHeapPool_;
	DescriptorHeapPool_Library[kDSV] = DSVdescriptorHeapPool_;
}


