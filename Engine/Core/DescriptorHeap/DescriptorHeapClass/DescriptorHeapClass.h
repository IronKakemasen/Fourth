#pragma once
#include "../DescriptorHeapContext.h"

class ViewCreator;

class DescriptorHeapClass
{
public:
	DescriptorHeapClass(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
		UINT handleIncrementSize_, uint32_t kMaxDescriptor_,bool shaderVisible_ ,std::string name_);

	struct AccessKey;
	
	//CPU / GPU / 生成数を返す
	template<typename HandleType>
	[[nodiscard]] HandleType GetHandle();

	//currentCreateNum(ビュー生成数)をインクリメントする
	void Increment(AccessKey accessKey_);

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	//ハンドルのインクリメントサイズ
	UINT handleIncrementSize{};
	//最大領域分割数
	uint32_t kMaxDescriptor{};
	//現在のviewの生成数
	uint32_t currentCreateNum{};
	//SRVかどうか
	bool shaderVisible{};
	//名前
	std::string name{};
};


template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapClass::GetHandle();

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapClass::GetHandle();

template<>
[[nodiscard]] uint32_t DescriptorHeapClass::GetHandle();

struct DescriptorHeapClass::AccessKey
{
private:

	//アクセスできるのはビュークリエイターのみ
	friend class ViewCreator;
	explicit AccessKey() = default;
};
