#include "PreCompileHeader.h"
#include "BufferAndResourcePicker.h"
#include "../../../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
#include "../../../../RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"





[[nodiscard]] std::tuple<GPUBufferBehavior*, ID3D12Resource*, std::string> BufferContext::BufferUploader::BufferAndResourcePicker::PickBufferAndResource
(
	BufferContext::BufferDispatcher* dispatcher_,
	BufferUniqueID id_
)
{
	GPUBufferBehavior* dstBuffer = dispatcher_->Dispatch(id_);
	ID3D12Resource* dstResource = dstBuffer->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 0);

	return std::make_tuple(dstBuffer, dstResource, dstBuffer->WatchName());
}
