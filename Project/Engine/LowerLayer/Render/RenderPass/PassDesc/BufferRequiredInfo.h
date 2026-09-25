#pragma once
#include "../../RenderContext.h"
#include "../../RenderStateComponent.h"


///そのパスで使用するバッファの情報をまとめたもの
struct RenderContext::RequiredBufferInfo
{
	struct ColorBuffer
	{
		std::string bufferName;
		DXGI_FORMAT format;
		std::vector<float> clearColor{};
		uint32_t width{};
		uint32_t height{};
		//シングル化ダブルか
		ProjectConfig::Render::NumBuffer numBuffer{};
		RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kDependsModel;
		BufferUniqueID bufferID;

		ColorBuffer() = default;
	};

	struct DepthStencilBuffer
	{
		DepthStencilBuffer() = default;

		std::string bufferName;
		DXGI_FORMAT dsvFormat;
		DXGI_FORMAT srvFormat;
		float clearDepth{};
		D3D12_CLEAR_FLAGS doesClearStencil;
		int clearStencil{};
		uint32_t width{};
		uint32_t height{};
		ProjectConfig::Render::NumBuffer numBuffer{};
		BufferUniqueID bufferID;

	};
};
