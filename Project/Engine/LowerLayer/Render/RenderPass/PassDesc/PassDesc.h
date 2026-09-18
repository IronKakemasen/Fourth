#pragma once
#include "BufferRequiredInfo.h"
#include "RenderPassState.h"

struct RenderContext::PassDesc
{
	PassDesc
	(
		std::string const name_,
		std::optional<std::pair<std::string, std::string >> const& ms_psFileName_,
		RenderPassState renderPassState_,
		std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> const& colorBuffersInfo_,
		std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> const& depthStencilBufferInfo_,
		std::vector <std::string> const& referenceBufferNames_
	);

	
	RenderPassState const& WatchRenderPassState()const;
	std::vector<RenderContext::RequiredBufferInfo::ColorBuffer> const& WatchColorBuffersInfo()const;
	std::optional<RenderContext::RequiredBufferInfo::DepthStencilBuffer> const& WatchDepthStencilBufferInfo()const;
	std::optional<std::pair<std::string, std::string >> const& WatchMs_PsFileName()const;

	void SetColorBufferUniqueID(BufferUniqueID id_, size_t index_);
	void SetDepthStencilBufferUniqueID(BufferUniqueID id_);

	void DebugLog()const;
	std::string const WatchName()const;
private:

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

