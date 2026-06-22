#include "PreCompileHeader.h"
#include "DepthStencilBuffer.h"


DepthStencilBuffer::DepthStencilBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_), std::move(description_))
{

}

float DepthStencilBuffer::WatchClearColor(ExtractMaterialKey key_)
{
	return static_cast<DepthStencilBufferDescription*>(description.get())->WatchParam().clearColor;
}

std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
DepthStencilBuffer::CreateNextStepBarriers(ExtractMaterialKey key_)
{
	return { D3D12_RESOURCE_BARRIER{}, D3D12_RESOURCE_BARRIER{} };
}
