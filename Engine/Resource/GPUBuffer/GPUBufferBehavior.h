#pragma once


struct GPUBufferBehavior
{
	struct InstanceKey;
	struct BufferAccessKey;

	GPUBufferBehavior(const InstanceKey& instanceKey , std::string name_);
	ID3D12Resource& GetResource( const BufferAccessKey& bufferAccessKey_ , int index_);
	void SetName(const InstanceKey& instanceKey);

private:

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	std::string name = "noName";
	
};


class GPUBufferCreator;
class GpuBufferManager;

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
	friend class GpuBufferManager;

	explicit BufferAccessKey() = default;
};
