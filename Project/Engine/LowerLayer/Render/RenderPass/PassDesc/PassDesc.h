#pragma once
#include "BufferRequiredInfo.h"
#include "../RenderPassState.h"

struct RenderContext::PassDesc
{
	friend class RenderContext;

	PassDesc
	(
		std::string const name_,
		std::optional<std::pair<std::string, std::string >> const& ms_psFileName_,
		RenderPassState renderPassState_,
		std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> const& colorBuffersInfo_,
		std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> const& depthStencilBufferInfo_,
		std::vector <std::string> const& referenceBufferNames_
	);

private:


	void DebugLog()const;

	//オフスクリーンパスの場合、シェーダーファイルは1つに限定される
	std::optional<std::pair<std::string, std::string >> ms_psFileName;

	//renderPassComponentの塊
	RenderPassState renderPassState;

	//必要なバッファの情報
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> colorBuffersInfo;
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> depthStencilBufferInfo;

	//参照するバッファ(テクスチャ)の名前一覧
	std::vector <std::string> referenceBufferNames;

	//デバッグ用
	std::string passName;

};

