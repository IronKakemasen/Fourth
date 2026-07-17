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

	void RecordingStart(const UsesResourceUploaderPermission& permission_);
	void WaitAndKick(const UsesResourceUploaderPermission& permission_);
	inline void Upload
	(
		const UsesResourceUploaderPermission& permission_,
		ID3D12Resource* dstResource_, 
		ID3D12Resource* intermediateResource_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	)
	{
		UpdateSubresources(commandList.Get(), dstResource_, intermediateResource_, 0, 0, subResourceCount_, subeResource_);
	}

private:

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
	ID3D12CommandQueue* commandQueue;
	Synchronizer* synchronizer;
};


