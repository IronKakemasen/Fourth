#pragma once
#include "../Synchronizer/Synchronizer.h"

class CommandContext::ResourceUploader
{

public:

	ResourceUploader
	(
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>&& allocator_forUpload_,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>&& cmdList_forUpload_,
		ID3D12CommandQueue* commandQueue_,
		Synchronizer* synchronizer_
	);

	void RecordingStart();
	void Wait();
	void Close(CommandContext::CloseKey key_);

private:

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	ID3D12CommandQueue* commandQueue;
	Synchronizer* synchronizer;

};

