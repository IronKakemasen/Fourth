#pragma once
#include "../SwapChainContext.h"


class SwapChainContext::Presenter
{
public:
	Presenter(IDXGISwapChain4* swapChain_);

	//現在のフレームインデックススを取得
	UINT GetFrameIndex(NexusFieldProof proof_, AgentKey agentKey_)const
	{
		return swapChain->GetCurrentBackBufferIndex();
	}

	//バックバッファインデックス入れ替え
	void Present()const
	{
		static auto const errorMsg = "swapChain->Presentでエラー";
		static auto const fileName = "Presenter.cpp";

		HRESULT hr = swapChain->Present(1, 0);
		ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), errorMsg, fileName);
	}

private:

	IDXGISwapChain4* swapChain;

};

