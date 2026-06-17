#pragma once
#include "../SwapChainColorBuffer/SwapChainColorBuffer.h"


//描画パスを構築するのに必要な材料を渡す
class SwapChainContext::RenderPassMaterialProvider
{
public:

	struct Materials
	{
		struct ColorBuffer
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle{};
			D3D12_RESOURCE_BARRIER barrier;
			D3D12_VIEWPORT* viewport;
			D3D12_RECT* scissorRect;
		};

		struct DepthStencilBuffer
		{
			D3D12_CPU_DESCRIPTOR_HANDLE dsvhandle{};
		};

		ColorBuffer colorBuffer;
		DepthStencilBuffer depthStencilBuffer;

		Materials(ColorBuffer colorBuffer_, DepthStencilBuffer depthStencilBuffer_)
			:colorBuffer(colorBuffer_), depthStencilBuffer(depthStencilBuffer_){}

	};


	RenderPassMaterialProvider(SwapChainContext::ColorBuffer* colorBuffer_);
	
	Materials Provide(UINT frameIndex_);

private:

	SwapChainContext::ColorBuffer* colorBuffer;
};

