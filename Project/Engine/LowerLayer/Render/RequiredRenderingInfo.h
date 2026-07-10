#pragma once


//描画パスを構築するのに必要な情報をまとめたディスクリプション
struct RequiredRenderingInfo
{
	///テクスチャとして読む	ときに必要
	struct Texture
	{
		//SRVヒープ上のインデックス
		uint32_t srvHeapIndex;
		//バリアを張るため
		D3D12_RESOURCE_BARRIER barrier;
	};

	///描画先として書き込むときに必要
	struct ColorBuffer
	{
		//RTVヒープ上のインデックス
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle{};
		//バリアを張るため
		D3D12_RESOURCE_BARRIER barrier{};
	};

	///描画先として書き込むときに必要
	struct DepthBuffer
	{
		//DSVヒープ上のインデックス
		D3D12_CPU_DESCRIPTOR_HANDLE dsvCpuHandle;
		//バリアを張るため
		D3D12_RESOURCE_BARRIER barrier;
	};
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
