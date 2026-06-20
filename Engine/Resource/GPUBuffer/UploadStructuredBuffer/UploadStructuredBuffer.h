#pragma once 
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"

struct UploadStructuredBufferDescription;

//読み書きStructuredBuffer
class UploadStructuredBuffer final : public GPUBufferBehavior
{

public:

	UploadStructuredBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
		CreateNextStepBarriers(ExtractMaterialKey key_)override;

private:


};

