#pragma once
#include "../BufferAssembler/BufferAssembler.h"


class GPUBufferManager;
struct BufferDescriptionBehavior;

class GPUBufferBehavior
{
public:

	//生成キー
	struct InstanceKey;
	//アクセスキー
	struct BufferAccessKey;

	GPUBufferBehavior
	(
		const InstanceKey& instanceKey_, 
		std::string name_, 
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, 
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	virtual ~GPUBufferBehavior();

	//生リソースを取得
	ID3D12Resource* GetResource( BufferAccessKey bufferAccessKey_ , int resourceNo_);
	
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

	//各種ビューのインデックスを取得
	template<ViewType type, typename Index>
	Index WatchIndex(uint8_t resourceNo_)const 
	{
		const auto& dstHeapContainer = buffers.at(resourceNo_).heapIndicesContainer[type];

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

protected:

	//自身を構成するディスクリプション
	std::unique_ptr <BufferDescriptionBehavior> description;

private:

	//各desctiptorheapのインデックス
	struct IndexSet
	{
		uint32_t uint{};
		D3D12_CPU_DESCRIPTOR_HANDLE cpu{};
		D3D12_GPU_DESCRIPTOR_HANDLE gpu{};
	};

	struct Buffer
	{
		////生リソース
		Microsoft::WRL::ComPtr<ID3D12Resource> resource;
		//各ビューのインデックス
		std::unordered_map<ViewType, IndexSet> heapIndicesContainer;
		//リソースステート
		D3D12_RESOURCE_STATES curState;

		//ステートを遷移するためのバリアを生成
		D3D12_RESOURCE_BARRIER CreateBarrier(D3D12_RESOURCE_STATES after_);
	};

	//複数分用意する
	std::array<Buffer, ProjectConfig::Render::kRequiredGPUBufferSum> buffers;
	
	//なまえ
	std::string name = "noName";
};



//生成できるのはBufferAssemblerのみ
struct GPUBufferBehavior::InstanceKey
{
private:

	friend class BufferContext::BufferAssembler;

	explicit InstanceKey() = default;
};


struct GPUBufferBehavior::BufferAccessKey
{
private:
	friend class BufferContext::BufferAssembler;
	friend class GPUBufferManager;

	explicit BufferAccessKey() = default;
};

