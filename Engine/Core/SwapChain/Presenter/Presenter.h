#pragma once
#include "../SwapChainContext.h"


class SwapChainContext::Presenter
{
public:
	Presenter(IDXGISwapChain4* swapChain_);

	//現在のフレームインデックススを取得
	UINT GetFrameIndex();
	//バックバッファインデックス入れ替え
	void Present();

private:

	IDXGISwapChain4* swapChain;

};

