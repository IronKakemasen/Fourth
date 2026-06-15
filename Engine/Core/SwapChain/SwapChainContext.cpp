#include "PreCompileHedder.h"
#include "SwapChainContext.h"
#include "SwapChainColorBuffer/SwapChainColorBuffer.h"
#include "../DescriptorHeap/ViewCreator/ViewCreator.h"


SwapChainContext::SwapChainContext
(
	InstanceKey instanceKey_,
	ViewCreator& viewCreator_,
	float clearColor_[4],
	DXGI_FORMAT format_
)
{
	CreateSwapChainColorBuffer(instanceKey_,viewCreator_, clearColor_, format_);

}

SwapChainContext::~SwapChainContext()
{

}

void SwapChainContext::CreateSwapChainColorBuffer
(
	InstanceKey instanceKey_,
	ViewCreator& viewCreator_,
	float clearColor_[4],
	DXGI_FORMAT format_
)
{
	colorBuffer.reset(new SwapChainContext::ColorBuffer(clearColor_, format_));

	//ビュー生成
	{
		auto rtvDesc = colorBuffer->CreateRTV_Desc();
		auto swapChainDesc = colorBuffer->CreateSwapChainDesc();
		ResourceGetKey resourceGetKey;

		for (int i = 0;i < ProjectConfig::Render::kRequiredGPUBufferSum;++i)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

			//Rtvを作成
			std::tie(std::ignore, rtvCPU, std::ignore) =
				viewCreator_.CreateView(colorBuffer->GetResource(resourceGetKey, i), rtvDesc);

			//インデックスを書き込む
			colorBuffer->OverrideHeapIndex(instanceKey_, i, rtvCPU);
		}
	}


}
