#pragma once


class GPUBufferCreator;
class GPUBufferManager;
class RTV_Creator;
class SRV_Creator;
class UAV_Creator;
struct BufferDescriptionBehavior;


class GPUBufferBehavior
{
public:

	//生成キー
	struct InstanceKey;
	//アクセスキー
	struct BufferAccessKey;
	//インデックス書き換えキー
	struct OverrideIndexKey;

	GPUBufferBehavior
	(
		const InstanceKey& instanceKey_, 
		std::string name_, 
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, 
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	virtual ~GPUBufferBehavior();

	ID3D12Resource& GetResource( const BufferAccessKey& bufferAccessKey_ , int index_);
	
	//descriptorHeapIndexを書き込む
	template<ViewType type, typename Index>
	inline void OverrideIndex(OverrideIndexKey overrideIndexKey_, Index index_)
	{
		heapIndices[type] = index_;
	}

	//indexを取得
	template<typename T>
	inline T GetHeapData(ViewType type) const
	{
		auto it = heapIndices.find(type);
		if (it != heapIndices.end())
		{
			return std::get<T>(it->second);
		}
		return T{}; 
	}

protected:

	std::unique_ptr <BufferDescriptionBehavior> description;

private:

	//リソースに名を刻む
	void SetName(const InstanceKey& instanceKey_);

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	std::string name = "noName";

	//各desctiptorheapのインデックス
	std::unordered_map<ViewType, std::variant<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE>> heapIndices;
};


struct GPUBufferBehavior::InstanceKey
{
private:

	friend class GPUBufferCreator;

	explicit InstanceKey() = default;
};


struct GPUBufferBehavior::BufferAccessKey
{
private:
	friend class GPUBufferCreator;
	friend class GPUBufferManager;

	explicit BufferAccessKey() = default;
};

//インデックスの書き換えはViewCreatorのみ可能
struct GPUBufferBehavior::OverrideIndexKey
{
private:

	friend class RTV_Creator;
	friend class SRV_Creator;
	friend class UAV_Creator;

	explicit OverrideIndexKey() = default;
};
