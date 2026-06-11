#pragma once


class GPUBufferCreator;
class GPUBufferManager;
class RTV_Creator;
class SRV_Creator;
class UAV_Creator;


class GPUBufferBehavior
{
public:

	//生成キー
	struct InstanceKey;
	//アクセスキー
	struct BufferAccessKey;
	//インデックス書き換えキー
	struct OverrideIndexKey;

	GPUBufferBehavior(const InstanceKey& instanceKey_, std::string name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_);
	ID3D12Resource& GetResource( const BufferAccessKey& bufferAccessKey_ , int index_);

private:

	//リソースに名を刻む
	void SetName(const InstanceKey& instanceKey_);

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	std::string name = "noName";
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
