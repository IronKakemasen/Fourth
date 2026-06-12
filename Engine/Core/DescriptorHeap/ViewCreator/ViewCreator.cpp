#include "PreCompileHedder.h"
#include "ViewCreator.h"


ViewCreator::ViewCreator
(
	DescriptorHeapContext::CreateKey createKey_,
	DescriptorHeapClass* RTVdescriptorHeapClass_,
	DescriptorHeapClass* SRVUAVdescriptorHeapClass_,
	DescriptorHeapClass* DSVdescriptorHeapClass_,
	DescriptorHeapContext::CreateRTVCommand rtvCmd_,
	DescriptorHeapContext::CreateSRVCommand srvCmd_,
	DescriptorHeapContext::CreateDSVCommand dsvCmd_,
	DescriptorHeapContext::CreateUAVCommand uavCmd_
) :rtvCmd(rtvCmd_), srvCmd(srvCmd_), dsvCmd(dsvCmd_), uavCmd(uavCmd_)
{
	descriptorHeap_map[kRTV] = RTVdescriptorHeapClass_;
	descriptorHeap_map[kSRVUAV] = SRVUAVdescriptorHeapClass_;
	descriptorHeap_map[kDSV] = DSVdescriptorHeapClass_;

}


