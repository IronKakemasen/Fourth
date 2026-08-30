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
		int clearStencil{};
		uint32_t width{};
		uint32_t height{};
		ProjectConfig::Render::NumBuffer numBuffer{};
		BufferUniqueID bufferID;

	};

	///テクスチャとして読む	ときに必要
	struct Texture
	{
		//SRVヒープ上のインデックス
		SRVHeapIndex srvHeapIndex{};
		//バリアを張るため
		D3D12_RESOURCE_BARRIER barrier{};
	};

	///描画先として書き込むときに必要
	struct RenderTarget
	{
		//RTVヒープ上のインデックス
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle{};
		//バリアを張るため
		D3D12_RESOURCE_BARRIER barrier{};
	};
};
