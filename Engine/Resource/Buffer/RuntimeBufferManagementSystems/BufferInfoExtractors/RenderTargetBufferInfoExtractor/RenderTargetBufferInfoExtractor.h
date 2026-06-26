#pragma once
#include "../../../BufferContext.h"
#include "../../../../../Render/RuntimeRenderingManagementSystems/RequiredRenderingInfo.h"

class BufferContext::RenderTargetBufferInfoExtractor
{

	//ユニークIDをもとに該当のバッファから描画パス構築に必要な情報を抽出する
	template<typename InfoType>
	InfoType Exstract(BufferContext::BufferUniqueID id_);

};

template<>
RequiredRenderingInfo::ColorBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(BufferContext::BufferUniqueID id_);

template<>
RequiredRenderingInfo::ColorBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(BufferContext::BufferUniqueID id_);

