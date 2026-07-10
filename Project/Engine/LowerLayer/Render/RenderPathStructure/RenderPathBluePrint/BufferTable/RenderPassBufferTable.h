#pragma once
#include "../RenderPathBluePrint.h"


struct RenderPathBluePrint::BufferTable
{
	///そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo
	{
		struct ColorBuffer
		{
			DXGI_FORMAT format;
			std::array<float, 4> clearColor{};
			uint32_t width{};
			uint32_t height{};

			ColorBuffer
			(
				DXGI_FORMAT format_,
				std::array<float, 4> clearColor_,
				uint32_t width_,
				uint32_t height_
			):format(format_), clearColor(clearColor_), width(width_), height(height_)
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
				float clearStencil_
			):dsvFormat(dsvFormat_), srvFormat(srvFormat_), clearDepth(clearDepth_), clearStencil(clearStencil_)
			{

			}
			DXGI_FORMAT dsvFormat;
			DXGI_FORMAT srvFormat;
			float clearDepth{};
			float clearStencil{};
		};

		std::vector<ColorBuffer> colorBuffers;
		std::optional<DepthStencilBuffer> depthStencilBuffer;

		void Add
		(
			DXGI_FORMAT format_,
			std::array<float, 4> clearColor_,
			uint32_t width_,
			uint32_t height_
		);

		void Add
		(
			DXGI_FORMAT dsvFormat_,
			DXGI_FORMAT srvFormat_,
			float clearDepth_,
			float clearStencil_
		);


	};

	RequiredBufferInfo BufferInfoTable(RenderPathComponent::Pass pass_);

};

