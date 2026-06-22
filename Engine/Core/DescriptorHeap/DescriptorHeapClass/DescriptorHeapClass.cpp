#include "PreCompileHeader.h"
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

	//フリーリストに空きインデックスを最大数まで登録
	for (uint32_t i = 0u;i < kMaxDescriptor_;++i)
	{
		freeList.emplace_back(i);
	}
}

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapClass::GetHandle(uint32_t index_)
{
	if (!shaderVisible) return D3D12_GPU_DESCRIPTOR_HANDLE{};

	D3D12_GPU_DESCRIPTOR_HANDLE handleStartGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE next;
	next.ptr = handleStartGPU.ptr + handleIncrementSize * index_;

	return next;
}

template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::GetHandle(uint32_t index_)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleStartCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_CPU_DESCRIPTOR_HANDLE next;
	next.ptr = handleStartCPU.ptr + handleIncrementSize * index_;

	return next;
}

std::tuple<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE>
DescriptorHeapClass::ProvideFreeHeapIndex(CreateViewKey accessKey_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		!freeList.empty(),
		name + " のヒープが枯渇",
		fileName
	);

	uint32_t lastIndex = freeList.back();
	freeList.pop_back();

	return std::make_tuple
	(
		lastIndex, 
		GetHandle<D3D12_CPU_DESCRIPTOR_HANDLE>(lastIndex),
		GetHandle<D3D12_GPU_DESCRIPTOR_HANDLE>(lastIndex)
	);
}

//空きヒープインデックスを回収
void DescriptorHeapClass::CollectHeapIndex(uint32_t index_, CollectHeapIndexKey key_)
{
	freeList.emplace_back(index_);
}
