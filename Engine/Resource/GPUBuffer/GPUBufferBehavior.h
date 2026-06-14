#pragma once


class GPUBufferManager;
struct BufferDescriptionBehavior;
class BufferAssembler;

class GPUBufferBehavior
{
private:

	//各desctiptorheapのインデックス
	struct IndexSet
	{
		uint32_t uint{};
		D3D12_CPU_DESCRIPTOR_HANDLE cpu;
		D3D12_GPU_DESCRIPTOR_HANDLE gpu;
	};

	//各ビューのインデックス
	std::array< std::unordered_map<ViewType, IndexSet>, ProjectConfig::Render::kRequiredGPUBufferSum> heapIndicesContainer;

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

	//生英ソースを取得
	ID3D12Resource* GetResource( BufferAccessKey bufferAccessKey_ , int resourceNo_);
	
	//descriptorHeapIndexを書き込む
	template<ViewType type, typename Index>
	void OverrideHeapIndex(InstanceKey instanceKey_, Index index_, uint8_t resourceNo_)
	{
		if constexpr (std::is_same_v<Index, uint32_t>)
		{
			heapIndicesContainer.at(resourceNo_)[type].uint = index_;
		}
		else if constexpr (std::is_same_v<Index, D3D12_CPU_DESCRIPTOR_HANDLE>)
		{
			heapIndicesContainer.at(resourceNo_)[type].cpu = index_;
		}
		else if constexpr (std::is_same_v<Index, D3D12_GPU_DESCRIPTOR_HANDLE>)
		{
			heapIndicesContainer.at(resourceNo_)[type].gpu = index_;
		}
	}

	//各種ビューのインデックスを取得
	template<ViewType type, typename Index>
	Index WatchIndex(uint8_t resourceNo_)const 
	{
		if constexpr (std::is_same_v<Index, uint32_t>)
		{
			return heapIndicesContainer.at(resourceNo_).at(type).uint;
		}
		else if constexpr (std::is_same_v<Index, D3D12_CPU_DESCRIPTOR_HANDLE>)
		{
			return heapIndicesContainer.at(resourceNo_).at(type).cpu;
		}
		else if constexpr (std::is_same_v<Index, D3D12_GPU_DESCRIPTOR_HANDLE>)
		{
			return heapIndicesContainer.at(resourceNo_).at(type).gpu;
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

	//生リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	//なまえ
	std::string name = "noName";
	//現在リソースステート
	D3D12_RESOURCE_STATES curState;
};



//生成できるのはBufferAssemblerのみ
struct GPUBufferBehavior::InstanceKey
{
private:

	friend class BufferAssembler;

	explicit InstanceKey() = default;
};


struct GPUBufferBehavior::BufferAccessKey
{
private:
	friend class BufferAssembler;
	friend class GPUBufferManager;

	explicit BufferAccessKey() = default;
};

