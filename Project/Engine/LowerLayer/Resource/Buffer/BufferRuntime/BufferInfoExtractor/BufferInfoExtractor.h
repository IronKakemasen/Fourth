#pragma once
#include "../../BufferContext.h"
#include "../../../../Render/RenderPass/PassDesc/BufferRequiredInfo.h"

//class DepthStencilBuffer;
//class ColorBuffer;
//struct IRenderTargetBuffer;
//class GPUBufferBehavior;
//
class BufferContext::BufferInfoExtractor
{
public:

	BufferInfoExtractor();

	////該当のバッファから描画パス構築に必要な情報を抽出する
	//template<typename InfoType,typename BufferType>
	//InfoType Exstract(BufferType* buffer_);

	////ダブルバッファを全てSwapさせる
	//void SwapApplicableBuffer();

private:

	//フレームの最後にスワップ対象のバッファを同時に処理するため
	std::vector<GPUBufferBehavior*> tmpBufferContainer;
	int const kBufferContainerSize = 64;
};
//
//
/////+///////////////////////////////////////////////////////////////////////////////////////////////////////
/////+///////////////////////////////////////////////////////////////////////////////////////////////////////
/////+///////////////////////////////////////////////////////////////////////////////////////////////////////
//template<>
//Pass::RequiredBufferInfo::Texture BufferContext::BufferInfoExtractor::Exstract(ColorBuffer* buffer_);
//
//template<>
//Pass::RequiredBufferInfo::RenderTarget BufferContext::BufferInfoExtractor::Exstract(ColorBuffer* buffer_);
//
//
//template<>
//Pass::RequiredBufferInfo::Texture BufferContext::BufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_);
//
//template<>
//Pass::RequiredBufferInfo::RenderTarget BufferContext::BufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_);
