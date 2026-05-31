#pragma once


struct GPUBufferBehavior
{
	struct CreateKey;
	struct BufferAccessKey;

	GPUBufferBehavior(const CreateKey& createKey_ , std::string name_);
	ID3D12Resource& GetResource( const BufferAccessKey& bufferAccessKey_ , int index_);
	void SetName(const CreateKey& createKey_);

private:

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, ProjectConfig::Render::kRequiredGPUBufferSum> resources;
	std::string name = "noName";
	
};

