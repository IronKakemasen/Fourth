#include "PreCompileHedder.h"
#include "ColorBuffer.h"
#include "../../BufferDescriptions/BufferDescriptionBehavior.h"


ColorBuffer::ColorBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_), std::move(description_))
{
	SetMatrix();
}


ColorBufferDescription ColorBuffer::WatchDescription() const
{
	return desc;
}


void ColorBuffer::SetMatrix()
{
	//クライアント領域と一緒のサイズにして画面全体に表示
	viewport.Width = static_cast<FLOAT>(desc.width);
	viewport.Height = static_cast<FLOAT>(desc.height);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//しざー矩形
	scissorRect.right = static_cast<LONG>(desc.width);
	scissorRect.bottom = static_cast<LONG>(desc.height);
	scissorRect.left = static_cast<LONG>(0.0f);
	scissorRect.top = static_cast<LONG>(0.0f);

}
