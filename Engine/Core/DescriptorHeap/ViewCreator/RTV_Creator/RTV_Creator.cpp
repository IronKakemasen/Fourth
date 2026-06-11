#include "PreCompileHedder.h"
#include "RTV_Creator.h"
#include "../../../../Resource/GPUBuffer/ColorBuffer/ColorBuffer.h"

RTV_Creator::RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior<D3D12_RENDER_TARGET_VIEW_DESC>(createKey_, descriptorHeapClass_)
{

}

void RTV_Creator::CreateView(GPUBufferBehavior& buffer_)
{
	ColorBuffer& colorBuffer = static_cast<ColorBuffer&>(buffer_);

	//ビュー生成数を取得
	uint32_t allocateIndex = descriptorHeapClass->WatchAllocateIndex();

	//ビュー生成数に応じたハンドルを返す
	auto handle = CalculateHandle<D3D12_CPU_DESCRIPTOR_HANDLE>();
	
	//リソースからディスクリプションを取得
	auto desc = colorBuffer.WatchDescription();

	//そのコンテナのインデックスをせっとする
	colorBuffer.OverrideIndex<ViewType::kRTV>(ColorBuffer::OverrideIndexKey{}, allocateIndex);
}


D3D12_RENDER_TARGET_VIEW_DESC RTV_Creator::CreateViewDesc()
{

	return D3D12_RENDER_TARGET_VIEW_DESC{};
}
