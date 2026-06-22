#include "PreCompileHeader.h"
#include "UploadStructuredBuffer.h"


std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
UploadStructuredBuffer::CreateNextStepBarriers(ExtractMaterialKey key_)
{
	return { D3D12_RESOURCE_BARRIER {},D3D12_RESOURCE_BARRIER{} };
}
