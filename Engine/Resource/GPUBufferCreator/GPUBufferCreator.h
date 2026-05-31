#pragma once


class WinApp;

class GPUBufferCreator
{
public:

	struct AccessKey
	{

	private:

		friend class WinApp;
		explicit AccessKey() = default;
	};

	GPUBufferCreator(AccessKey accessKey_ , ID3D12Device8* device_);


private:

	ID3D12Device8* device;
};

