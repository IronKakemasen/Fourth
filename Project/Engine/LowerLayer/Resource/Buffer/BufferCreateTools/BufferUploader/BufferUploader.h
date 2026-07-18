#pragma once
#include "../../BufferContext.h"
#include "../../../../Core/Command/CommandContext.h"

class GPUBufferBehavior;

class BufferContext::BufferUploader
{
public:

	BufferUploader
	(
		BufferContext::InstanceKey key_,
		BufferContext::ResourceCreator* resourceCreator_,
		CommandContext* commandContext_
	);

	~BufferUploader();

	void Upload
	(
		GPUBufferBehavior* dstBuffer_,
		UINT dstResourceSize_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	);

private:
	BufferContext::ResourceCreator* resourceCreator;
	CommandContext::UploadCommand uploadCommand;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> intermediateResources;
	
	D3D12_RESOURCE_DESC CreateIntermedeiteResourceDesc(UINT resourceSize_)const;
	D3D12_HEAP_PROPERTIES CreateIntermedeiteHeapProp()const;
};

