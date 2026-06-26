#include "PreCompileHeader.h"
#include "UploadStructuredBuffer.h"
#include "../../BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"


UploadStructuredBuffer::UploadStructuredBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resourceContainer_), std::move(description_))
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
