#pragma once


class WinApp;

class GPUBufferCreator
{
public:

	struct CreateKey;

	GPUBufferCreator(CreateKey createKey_, ID3D12Device8* device_);


private:

	ID3D12Device8* device;
};



struct GPUBufferCreator::CreateKey
{

private:

	friend class WinApp;
	explicit CreateKey() = default;
};
