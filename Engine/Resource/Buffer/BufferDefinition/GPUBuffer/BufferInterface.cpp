#include "BufferInterface.h"


std::pair<D3D12_VIEWPORT, D3D12_RECT> IColorBuffer::OutMatrix()const
{
	return { viewport ,scissorRect };
}

void IColorBuffer::AssembleMatrix(UINT width_, UINT height_)
{
	//クライアント領域と一緒のサイズにして画面全体に表示
	viewport.Width = static_cast<FLOAT>(width_);
	viewport.Height = static_cast<FLOAT>(height_);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//シザー矩形
	scissorRect.right = static_cast<LONG>(width_);
	scissorRect.bottom = static_cast<LONG>(height_);
	scissorRect.left = static_cast<LONG>(0.0f);
	scissorRect.top = static_cast<LONG>(0.0f);

	Logger::Log("Structure:  Matrix", "BufferInterface.cpp");
}
