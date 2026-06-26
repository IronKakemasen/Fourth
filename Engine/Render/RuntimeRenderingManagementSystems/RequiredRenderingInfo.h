#pragma once


//描画パスを構築するのに必要な情報をまとめたディスクリプション
struct RequiredRenderingInfo
{
	struct ColorBuffer
	{
		///描画先として書き込むときに必要
		struct AsWiring
		{
			//RTVヒープ上のインデックス
			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
			//レンダーターゲットをクリアするため
			std::array<float, 4> clearColor;
			////バリアを張るため
			//std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum> barriers;
			//横幅
			uint32_t width{};
			//立幅
			uint32_t height{};

		};

		///テクスチャとして読むときに必要
		struct AsReading
		{
			//SRVヒープ上のインデックス
			uint32_t srvHeapIndex;
		};

		///PSOを構築するときに必要
		struct AsAssemblingPSO
		{
			DXGI_FORMAT format;
		};
	};

///+//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct DepthBuffer
	{
		///描画先として書き込むときに必要
		struct AsWriting
		{
			//DSVヒープ上のインデックス
			D3D12_CPU_DESCRIPTOR_HANDLE dsvCpuHandle;
			//横幅
			uint32_t width{};
			//立幅
			uint32_t height{};
			//クリアするため
			float clearDepth;
			UINT8 clearStencil;			
			////バリアを張るため
			//std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum> barriers;

		};

		///テクスチャとして読むときに必要
		struct AsReading
		{
			//SRVヒープ上のインデックス
			uint32_t srvHeapIndex;
		};

		///PSOを構築するときに必要
		struct AsAssemblingPSO
		{
			DXGI_FORMAT dsvFormat;
		};
	};
///+//////////////////////////////////////////////////////////////////////////////////////////////////////////////

};


//void IColorBuffer::AssembleMatrix(UINT width_, UINT height_)
//{
//	//クライアント領域と一緒のサイズにして画面全体に表示
//	viewport.Width = static_cast<FLOAT>(width_);
//	viewport.Height = static_cast<FLOAT>(height_);
//	viewport.TopLeftX = 0.0f;
//	viewport.TopLeftY = 0.0f;
//	viewport.MinDepth = 0.0f;
//	viewport.MaxDepth = 1.0f;
//
//	//シザー矩形
//	scissorRect.right = static_cast<LONG>(width_);
//	scissorRect.bottom = static_cast<LONG>(height_);
//	scissorRect.left = static_cast<LONG>(0.0f);
//	scissorRect.top = static_cast<LONG>(0.0f);
//
//	Logger::Log("Structure:  Matrix", "BufferInterface.cpp");
//}
