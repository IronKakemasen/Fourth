#pragma once
#include "../DescriptorHeapContext.h"
#include "../../../../Utility/SimpleFreeList/SimpleFreeList.h"

class ViewCreator;

class DescriptorHeapPool
{
public:

	//ビュークリエイターのみビュー生成可能
	struct CreateViewKey;
	//ヒープインデックスを触るための許可証
	struct CollectHeapIndexKey;

	DescriptorHeapPool(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_,
		UINT handleIncrementSize_, uint32_t kMaxDescriptor_,bool shaderVisible_ ,std::string name_);
	~DescriptorHeapPool();
	
	//フリーヒープインデックスを提供
	std::tuple<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE>
	ProvideFreeHeapIndex(CreateViewKey accessKey_);

	//ヒープインデックスを回収
	void CollectHeapIndex(uint32_t index_, CollectHeapIndexKey key_);

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	//ハンドルのインクリメントサイズ
	UINT handleIncrementSize{};
	//最大領域分割数
	uint32_t kMaxDescriptor{};
	//SRVかどうか
	bool shaderVisible{};
	//名前
	std::string name{};
	//使用可能インデックスのリスト
	SimpleFreeList freeList;

	//CPU / GPU ハンドルを返す
	template<typename HandleType>
	[[nodiscard]] HandleType GetHandle(uint32_t index_);

};

struct DescriptorHeapPool::CreateViewKey
{
private:

	//アクセスできるのはビュークリエイターのみ
	friend class ViewCreator;
	explicit CreateViewKey() = default;
};


///未定
struct DescriptorHeapPool::CollectHeapIndexKey
{
private:


	explicit CollectHeapIndexKey() = default;
};

template<>
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapPool::GetHandle(uint32_t index_);

template<>
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapPool::GetHandle(uint32_t index_);
