#pragma once
#include "../DescriptorHeapContext.h"

class ViewCreator;

class DescriptorHeapClass
{
public:
	DescriptorHeapClass(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
		UINT handleIncrementSize_, uint32_t kMaxDescriptor_, std::string name_);

	struct AccessKey;
	
	//currentCreateNumまたはCPUHandle(ビュー生成数)を返す
	template<typename HandleType>
	[[nodiscard]] HandleType WatchAllocateIndex();

	//CPU / GPUの次のハンドルを計算し返したあと、currentCreateNum(ビュー生成数)をインクリメントする
	template<typename HandleType>
	[[nodiscard]] HandleType CalculateHandleThenIncrement(AccessKey accessKey_);


private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	//ハンドルのインクリメントサイズ
	UINT handleIncrementSize{};
	//最大領域分割数
	uint32_t kMaxDescriptor{};
	//現在のviewの生成数
	uint32_t currentCreateNum{};
	//名前
	std::string name{};
};

template<>
[[nodiscard]] uint32_t DescriptorHeapClass::WatchAllocateIndex();

template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::WatchAllocateIndex();


template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::CalculateHandleThenIncrement(AccessKey accessKey_);

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapClass::CalculateHandleThenIncrement(AccessKey accessKey_);

struct DescriptorHeapClass::AccessKey
{
private:

	//アクセスできるのはビュークリエイターのみ
	friend class ViewCreator;
	explicit AccessKey() = default;
};
