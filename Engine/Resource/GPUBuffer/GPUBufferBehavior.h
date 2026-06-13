#pragma once


class GPUBufferManager;
struct IBufferDescription;
class BufferAssembler;

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
		std::unique_ptr <IBufferDescription>&& description_
	);

	virtual ~GPUBufferBehavior();

	ID3D12Resource* GetResource( const BufferAccessKey& bufferAccessKey_ , int index_);
	
	//descriptorHeapIndexを書き込む
	template<ViewType type, typename Index>
	inline void OverrideIndex(InstanceKey instanceKey_, Index index_,uint8_t resourceNo_)
	{
		heapIndices[type][resourceNo_] = index_;
	}

	//descriptorHeapIndexを取得
	template<ViewType type, typename Index>
	[[nodiscard]] Index WatchIndex(uint8_t resourceNo_) const
	{
		const auto& variantVal = heapIndices.at(type)[resourceNo_];

		ErrorMessageOutput::Assert::DetectError
		(
			std::holds_alternative<Index>(variantVal),
			"要求しているインデクスの型が不一致","GPUBufferBehavior.h"
		);

		return std::get<Index>(variantVal);
	}

protected:

	std::unique_ptr <IBufferDescription> description;

private:

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	std::string name = "noName";

	//各desctiptorheapのインデックス
	std::unordered_map<ViewType, 
		std::array<std::variant<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE> , ProjectConfig::Render::kMaximumShaderModel>> heapIndices;
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

