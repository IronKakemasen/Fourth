#pragma once
#include "../../../BufferContext.h"
#include "../../../../../Render/RequiredRenderingInfo.h"

class DepthStencilBuffer;
class ColorBuffer;
struct IRenderTargetBuffer;

class BufferContext::RenderTargetBufferInfoExtractor
{
public:

	RenderTargetBufferInfoExtractor();

	//該当のバッファから描画パス構築に必要な情報を抽出する
	template<typename InfoType,typename BufferType>
	InfoType Exstract(BufferType* buffer_);

	//ダブルバッファを全てSwapさせる
	void SwapApplicableBuffer();

private:

	//フレームの最後にスワップ対象のバッファを同時に処理するため
	std::vector<GPUBufferBehavior*> tmpBufferContainer;
	int const kBufferContainerSize = 64;
};


///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
RequiredRenderingInfo::ColorBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(ColorBuffer* buffer_);

template<>
RequiredRenderingInfo::Texture BufferContext::RenderTargetBufferInfoExtractor::Exstract(ColorBuffer* buffer_);

template<>
RequiredRenderingInfo::Format BufferContext::RenderTargetBufferInfoExtractor::Exstract(ColorBuffer* buffer_);

///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
RequiredRenderingInfo::DepthBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_);

template<>
RequiredRenderingInfo::Format BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_);

template<>
RequiredRenderingInfo::Texture BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_);
