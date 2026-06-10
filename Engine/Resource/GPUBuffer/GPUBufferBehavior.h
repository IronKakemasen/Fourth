#pragma once


class GPUBufferCreator;
class GPUBufferManager;

class GPUBufferBehavior
{
public:
	struct InstanceKey;
	struct BufferAccessKey;

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
