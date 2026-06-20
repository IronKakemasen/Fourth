#include "PreCompileHeader.h"
#include "ColorBuffer.h"
#include "../../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"


ColorBuffer::ColorBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_), std::move(description_))
{

}

std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
ColorBuffer::CreateNextStepBarriers(ExtractMaterialKey key_)
{
	return { D3D12_RESOURCE_BARRIER{}, D3D12_RESOURCE_BARRIER{} };
}


const ColorBufferDescription& ColorBuffer::WatchDescription() 
{
	return static_cast<ColorBufferDescription&>(*description.get());
}


void ColorBuffer::AssembleMatrix()
{
	const auto& param = static_cast<ColorBufferDescription&>(*description.get()).WatchParam();

	//クライアント領域と一緒のサイズにして画面全体に表示
	viewport.Width = static_cast<FLOAT>(param.width);
	viewport.Height = static_cast<FLOAT>(param.height);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//しざー矩形
	scissorRect.right = static_cast<LONG>(param.width);
	scissorRect.bottom = static_cast<LONG>(param.height);
	scissorRect.left = static_cast<LONG>(0.0f);
	scissorRect.top = static_cast<LONG>(0.0f);
}
