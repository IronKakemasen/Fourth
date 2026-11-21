#pragma once
#include "../../RenderContext.h"
#include "../../../../LowerLayer/RenderStateComponent.h"


///そのパスで使用するバッファの情報をまとめたもの
struct RenderContext::RequiredBufferInfo
{
	struct ColorBuffer
	{
		ColorBuffer() = default;

		std::string bufferName;
		DXGI_FORMAT format;
		//クリアするかどうか。自前バッファであればtrue。witesharing用との区別のため
		bool doClear = true;
		std::vector<float> clearColor{};
		uint32_t width{};
		uint32_t height{};
		//シングルかダブルか
		ProjectConfig::Render::NumBuffer numBuffer{};
		RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kDependsModel;
		BufferUniqueID bufferID = kInvalid;

	};

	struct DepthStencilBuffer
	{
		DepthStencilBuffer() = default;

		bool doClear = true;

		std::string bufferName;
		DXGI_FORMAT dsvFormat;
		DXGI_FORMAT srvFormat;
		float clearDepth{};
		D3D12_CLEAR_FLAGS doesClearStencil;
		int clearStencil{};
		uint32_t width{};
		uint32_t height{};
		ProjectConfig::Render::NumBuffer numBuffer{};
		BufferUniqueID bufferID = kInvalid;

	};
};
