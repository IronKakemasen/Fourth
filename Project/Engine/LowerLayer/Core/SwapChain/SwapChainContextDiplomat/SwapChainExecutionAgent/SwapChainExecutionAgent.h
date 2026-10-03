#pragma once
#include "../../SwapChainContext.h"


class SwapChainContext::ExecutionAgent
{
public:

	ExecutionAgent(NexusFieldProof proof_, Presenter& presenter_);

	//ランタイムでのpresent()を代行する
	UINT GetFrameIndex(NexusFieldProof proof_)const;

	//ランタイムでのフレームインデックス取得関数呼び出しを代行する
	void Present(NexusFieldProof proof_)const;



private:

	Presenter& presenter;

};

