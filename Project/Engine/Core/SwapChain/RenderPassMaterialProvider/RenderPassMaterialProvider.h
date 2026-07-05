#pragma once
#include "../SwapChainColorBuffer/SwapChainColorBuffer.h"


class DepthStencilBuffer;

//描画パスを構築するのに必要な材料を渡す
class SwapChainContext::RenderPassMaterialProvider
{
	struct Materials
	{
		struct ColorBuffer
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle{};
			D3D12_RESOURCE_BARRIER barrier;
			D3D12_VIEWPORT* viewport;
			D3D12_RECT* scissorRect;
			std::array<FLOAT, 4> clearColor;
		};

		struct DepthStencilBuffer
		{
			D3D12_CPU_DESCRIPTOR_HANDLE dsvhandle{};
			float clearColor{};
		};

		ColorBuffer colorBuffer;
		DepthStencilBuffer depthStencilBuffer;

		Materials(ColorBuffer colorBuffer_, DepthStencilBuffer depthStencilBuffer_)
			:colorBuffer(colorBuffer_), depthStencilBuffer(depthStencilBuffer_) {}

	};

public:

	RenderPassMaterialProvider(SwapChainContext::ColorBuffer* colorBuffer_, DepthStencilBuffer* depthStencilBuffer_);
	
	[[nodiscard]] Materials ProvideForBegine(UINT frameIndex_);
	[[nodiscard]] D3D12_RESOURCE_BARRIER ProvideEnd(UINT frameIndex_);

private:

	SwapChainContext::ColorBuffer* colorBuffer;
	DepthStencilBuffer* depthStencilBuffer;
};

