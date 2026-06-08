#include "PreCompileHedder.h"
#include "DescriptorHeapClass.h"

DescriptorHeapClass::DescriptorHeapClass(
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
	UINT handleIncrementSize_, uint32_t kMaxDescriptor_) :
	descriptorHeap(descriptorHeap_), handleIncrementSize(handleIncrementSize_), kMaxDescriptor(kMaxDescriptor_)
{

}

