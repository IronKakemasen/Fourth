#pragma once 
#include "../BufferInterface.h"

struct UploadStructuredBufferDescription;

//読み書きStructuredBuffer
class UploadStructuredBuffer final : public GPUBufferBehavior
{

public:

	UploadStructuredBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

private:


};

