#include "PreCompileHedder.h"
#include "DescriptorHeapClass.h"

namespace
{
	std::string fileName = "DescriptorHeapClass.cpp";
}


DescriptorHeapClass::DescriptorHeapClass
(
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
	UINT handleIncrementSize_, 
	uint32_t kMaxDescriptor_, 
	bool shaderVisible_, 
	std::string name_
) : descriptorHeap(descriptorHeap_), handleIncrementSize(handleIncrementSize_), kMaxDescriptor(kMaxDescriptor_),shaderVisible(shaderVisible_), name(name_)
{
	std::string log = "Instantiate: " + name_ + "[" + std::to_string(kMaxDescriptor_) + "]";
	Logger::Log(log, fileName);

}

void DescriptorHeapClass::Increment(DescriptorHeapClass::AccessKey accessKey_)
{
	currentCreateNum++;
}

template<>
[[nodiscard]] uint32_t DescriptorHeapClass::GetHandle()
{
	return currentCreateNum;
}

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapClass::GetHandle()
{
	if (!shaderVisible) return D3D12_GPU_DESCRIPTOR_HANDLE{};

	D3D12_GPU_DESCRIPTOR_HANDLE handleStartGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE next;
	next.ptr = handleStartGPU.ptr + handleIncrementSize * currentCreateNum;

	return next;
}

template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::GetHandle()
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleStartCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_CPU_DESCRIPTOR_HANDLE next;
	next.ptr = handleStartCPU.ptr + handleIncrementSize * currentCreateNum;

	return next;
}
