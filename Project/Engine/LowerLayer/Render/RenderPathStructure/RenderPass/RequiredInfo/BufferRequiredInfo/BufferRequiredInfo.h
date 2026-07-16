#pragma once
#include "../../RenderPass.h"


///そのパスで使用するバッファの情報をまとめたもの
struct RenderPath::Pass::RequiredBufferInfo
{
	struct ColorBuffer
	{
		DXGI_FORMAT format;
		std::array<float, 4> clearColor{};
		uint32_t width{};
		uint32_t height{};
		//Pass間でバインドするときに使用
		std::string name = "";
		BufferUniqueID bufferID;

		ColorBuffer
		(
			DXGI_FORMAT format_,
			std::array<float, 4> clearColor_,
			uint32_t width_,
			uint32_t height_,
			std::string name_
		) :format(format_), clearColor(clearColor_), width(width_), height(height_), name(name_)
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
			std::string name_
		) :dsvFormat(dsvFormat_), srvFormat(srvFormat_), clearDepth(clearDepth_), clearStencil(clearStencil_), name(name_)
		{

		}
		DXGI_FORMAT dsvFormat;
		DXGI_FORMAT srvFormat;
		float clearDepth{};
		float clearStencil{};
		std::string name = "";
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

	std::vector<ColorBuffer> colorBuffers;
	std::optional<DepthStencilBuffer> depthStencilBuffer;

	void Add
	(
		DXGI_FORMAT format_,
		std::array<float, 4> clearColor_,
		uint32_t width_,
		uint32_t height_,
		std::string name_
	);

	void Add
	(
		DXGI_FORMAT dsvFormat_,
		DXGI_FORMAT srvFormat_,
		float clearDepth_,
		float clearStencil_,
		std::string name_
	);
};
