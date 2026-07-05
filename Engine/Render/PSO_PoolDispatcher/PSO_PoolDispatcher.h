#pragma once
#include "../RenderContext.h"



class RenderContext::PSO_PoolDispatcher
{
public:
	PSO_PoolDispatcher
	(
		RenderContext::InstacnceKey key_ , 
		std::vector<ID3D12PipelineState*>* graphicsPSO_pool_
	);
	

private:
	std::vector<ID3D12PipelineState*>* graphicsPSO_pool;

};

