#pragma once
#include "../SwapChainContext.h"


class SwapChainContext::Presenter
{
public:
	Presenter(IDXGISwapChain4* swapChain_);

	//現在のフレームインデックススを取得
	UINT GetFrameIndex()const;
	//バックバッファインデックス入れ替え
	void Present()const;

private:

	IDXGISwapChain4* swapChain;

};

