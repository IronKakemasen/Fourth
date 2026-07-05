#pragma once
#include "../../BufferContext.h"
#include "../../../../Core/SwapChain/SwapChainContext.h"

struct BufferDescriptionBehavior;

class GPUBufferBehavior
{
	//各desctiptorheapのインデックス
	struct IndexSet
	{
		uint32_t uint{};
		D3D12_CPU_DESCRIPTOR_HANDLE cpu{};
		D3D12_GPU_DESCRIPTOR_HANDLE gpu{};
	};

	struct Buffer
	{
		//生リソース
		Microsoft::WRL::ComPtr<ID3D12Resource> resource;
		//各ビューのインデックス
		std::unordered_map<ViewType, IndexSet> heapIndicesContainer;
		//ステートを遷移するためのバリアを生成
		D3D12_RESOURCE_BARRIER CreateBarrier(D3D12_RESOURCE_STATES after_);
		//リソースステート
		D3D12_RESOURCE_STATES curResourceState;
	};

	//なまえ
	std::string name = "noName";

public:

	//生成キー
	struct InstanceKey;
	//生リソースアクセスキー
	struct ResourceAccessKey;
	//バッファから描画パスに必要な情報をもらうためのキー
	struct ExtractMaterialKey;

	GPUBufferBehavior
	(
		const InstanceKey& instanceKey_, 
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	virtual ~GPUBufferBehavior();

	//生リソースを取得
	ID3D12Resource* GetResource(ResourceAccessKey resourceAccessKey_ , int resourceNo_);
	
	//descriptorHeapIndexを書き込む
	template<ViewType type, typename Index>
	void OverrideHeapIndex(InstanceKey instanceKey_, Index index_, uint8_t resourceNo_)
	{
		auto& dstHeapContainer = buffers.at(resourceNo_).heapIndicesContainer[type];

		if constexpr (std::is_same_v<Index, uint32_t>)
		{
			dstHeapContainer.uint = index_;
		}
		else if constexpr (std::is_same_v<Index, D3D12_CPU_DESCRIPTOR_HANDLE>)
		{
			dstHeapContainer.cpu = index_;
		}
		else if constexpr (std::is_same_v<Index, D3D12_GPU_DESCRIPTOR_HANDLE>)
		{
			dstHeapContainer.gpu = index_;
		}
	}


protected:

	//自身を構成するディスクリプション
	std::unique_ptr <BufferDescriptionBehavior> description;

	//バッファ本体
	std::vector<Buffer> buffers;

	//各種ビューのインデックスを取得
	template<ViewType type, typename Index>
	Index WatchIndex(uint8_t resourceNo_)const
	{
		const auto& dstHeapContainer = buffers.at(resourceNo_).heapIndicesContainer.at(type);

		if constexpr (std::is_same_v<Index, uint32_t>)
		{
			return dstHeapContainer.uint;
		}
		else if constexpr (std::is_same_v<Index, D3D12_CPU_DESCRIPTOR_HANDLE>)
		{
			return dstHeapContainer.cpu;
		}
		else if constexpr (std::is_same_v<Index, D3D12_GPU_DESCRIPTOR_HANDLE>)
		{
			return dstHeapContainer.gpu;
		}
		else
		{
			ErrorMessageOutput::Assert::DetectError((false), "IndexTypeError", "GPUBufferBehavior.h");
		}

		return Index{};
	}

};



//生成できるのはBufferAssemblerのみ
struct GPUBufferBehavior::InstanceKey
{
private:

	friend class BufferContext::BufferAssembler;

	explicit InstanceKey() = default;
};


struct GPUBufferBehavior::ResourceAccessKey
{
private:
	friend class BufferContext::BufferAssembler;

	explicit ResourceAccessKey() = default;
};


struct GPUBufferBehavior::ExtractMaterialKey
{
private:
	
	friend class SwapChainContext::RenderPassMaterialProvider;

	explicit ExtractMaterialKey() = default;

};