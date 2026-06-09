#include "PreCompileHedder.h"
#include "RTV_Creator.h"
#include "../../../../Resource/GPUBuffer/ColorBuffer/ColorBuffer.h"

RTV_Creator::RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer_)
	:ViewCreatorBehavior(createKey_, descriptorHeapClass_), RTV_descriptorHandleCPUContainer(RTV_descriptorHandleCPUContainer_)
{

}

void RTV_Creator::CreateView(GPUBufferBehavior& buffer_)
{
	ColorBuffer& colorBuffer = static_cast<ColorBuffer&>(buffer_);
	auto handle = CalculateNextHandle<D3D12_CPU_DESCRIPTOR_HANDLE>();
	
	//ハンドルをコンテナに入れる
	RTV_descriptorHandleCPUContainer->emplace_back(handle);

	//リソースからディスクリプションを取得
	auto desc = colorBuffer.WatchDescription();


	//そのコンテナのインデックスをせっとする
	colorBuffer.OverrideIndex(ColorBuffer::OverrideIndexKey{}, currentCreateNum++);
}

void RTV_Creator::SetCommand(std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE, UINT, bool)> command_)
{

}
