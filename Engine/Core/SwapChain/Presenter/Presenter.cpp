#include "PreCompileHeader.h"
#include "Presenter.h"


SwapChainContext::Presenter::Presenter(IDXGISwapChain4* swapChain_)
	:swapChain(swapChain_)
{

}

UINT SwapChainContext::Presenter::GetFrameIndex()
{
	return swapChain->GetCurrentBackBufferIndex();
}


void SwapChainContext::Presenter::Present()
{
	swapChain->Present(1, 0);
}
