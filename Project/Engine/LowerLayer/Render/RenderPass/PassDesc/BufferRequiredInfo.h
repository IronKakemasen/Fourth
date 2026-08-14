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
		BufferUniqueID bufferID;

		ColorBuffer
		(
			DXGI_FORMAT format_,
			std::vector<float> clearColor_,
			uint32_t width_,
			uint32_t height_,
			std::string name_,
			BufferUniqueID bufferID_
		) :format(format_), clearColor(clearColor_), width(width_), height(height_), bufferID(bufferID_)
		{

		}
	};

	struct DepthStencilBuffer
	{
		DepthStencilBuffer
		(
			DXGI_FORMAT dsvFormat_,
			DXGI_FORMAT srvFormat_,
			float clearDepth_,
			float clearStencil_,
			std::string name_,
			BufferUniqueID bufferID_
		) :dsvFormat(dsvFormat_), srvFormat(srvFormat_), clearDepth(clearDepth_), clearStencil(clearStencil_), bufferID(bufferID_)
		{

		}
		DXGI_FORMAT dsvFormat;
		DXGI_FORMAT srvFormat;
		float clearDepth{};
		float clearStencil{};
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
