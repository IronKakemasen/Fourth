#pragma once
#include "../DescriptorHeapContext.h"

template<typename ViewDescType> class ViewCreatorBehavior;

class DescriptorHeapClass
{
public:
	DescriptorHeapClass(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
		UINT handleIncrementSize_, uint32_t kMaxDescriptor_, std::string name_);

	struct AccessKey;
	
	//currentCreateNum(ビュー生成数)を返す、その数をインクリメントする
	[[nodiscard]] uint32_t WatchAllocateIndex();

	//CPU / GPUの次のハンドルを計算し返したあと、currentCreateNum(ビュー生成数)をインクリメントする
	template<typename HandleType>
	[[nodiscard]] HandleType CalculateHandle(AccessKey accessKey_);

	//ID3D12DescriptorHeap* GetDescriptorHeap(AccessKey accessKey_);

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
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::CalculateHandle(AccessKey accessKey_);

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapClass::CalculateHandle(AccessKey accessKey_);

struct DescriptorHeapClass::AccessKey
{
private:

	//アクセスできるのはビュークリエイターのみ
	template<typename ViewDescType> friend class ViewCreatorBehavior;
	explicit AccessKey() = default;
};
