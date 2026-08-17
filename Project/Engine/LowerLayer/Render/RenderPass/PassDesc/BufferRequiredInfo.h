#pragma once
#include "../../RenderContext.h"


///そのパスで使用するバッファの情報をまとめたもの
struct RenderContext::RequiredBufferInfo
{
	struct ColorBuffer
	{
		DXGI_FORMAT format;
		std::vector<float> clearColor{};
		uint32_t width{};
		uint32_t height{};
		ProjectConfig::Render::NumBuffer numBuffer{};
		BufferUniqueID bufferID;

		ColorBuffer() = default;
	};

	struct DepthStencilBuffer
	{
		DepthStencilBuffer() = default;

		DXGI_FORMAT dsvFormat;
		DXGI_FORMAT srvFormat;
		float clearDepth{};
		float clearStencil{};
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
