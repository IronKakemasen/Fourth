#include "PreCompileHedder.h"
#include "DescriptorHeapClass.h"
#include "../ViewCreator/ViewCreatorBehavior.h"

namespace
{
	std::string fileName = "DescriptorHeapClass.cpp";
}


DescriptorHeapClass::DescriptorHeapClass(
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
	UINT handleIncrementSize_, uint32_t kMaxDescriptor_,std::string name_) :
	descriptorHeap(descriptorHeap_), handleIncrementSize(handleIncrementSize_), kMaxDescriptor(kMaxDescriptor_),name(name_)
{
	std::string log = "Instantiate: " + name_ + "[" + std::to_string(kMaxDescriptor_) + "]";
	Logger::Log(log, fileName);

}

[[nodiscard]]uint32_t DescriptorHeapClass::WatchAllocateIndex()
{
	ErrorMessageOutput::Assert::DetectError((currentCreateNum > kMaxDescriptor),
		name + "がリミットブレイク!", fileName);

	return currentCreateNum;
}

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapClass::CalculateHandle(AccessKey accessKey_)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleStartGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE next;
	next.ptr = handleStartGPU.ptr + handleIncrementSize * currentCreateNum++;

	return next;
}

template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::CalculateHandle(AccessKey accessKey_)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleStartCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_CPU_DESCRIPTOR_HANDLE next;
	next.ptr = handleStartCPU.ptr + handleIncrementSize * currentCreateNum++;

	return next;
}
