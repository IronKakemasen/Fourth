#pragma once
#include "../PSO_Context.h"
#include "PipelineStateDesc.h"

class ShaderLibrary;

class PSO_Context::Assembler
{

public:

	Assembler
	(
		PSO_Context::InstanceKey key_,
		CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
		CommandCreateComputePSO cmdCreateComputePSO_
	);

	Microsoft::WRL::ComPtr<ID3D12PipelineState> AssembleGraphicsPSO
	(
		PipelineStateDesc::ShaderSet shaderSet_,
		PipelineStateDesc::RenderTargetDesc renderTargetDesc_,
		PipelineStateDesc::RasterizerDesc rasterizerDesc_,
		PipelineStateDesc::DepthStencilDesc depthStencilDesc_,
		PipelineStateDesc::SampleDesc sampleDesc_,
		ID3D12RootSignature* rootSignature_
	);

private:

	//PSO生成コマンド
	CommandCreateGraphicsPSO cmdCreateGraphicsPSO;
	CommandCreateComputePSO cmdCreateComputePSO;

	//要項チェック
	void Check(const PipelineStateDesc::ShaderSet& shaderSet_,const PipelineStateDesc::RenderTargetDesc& renderTargetDesc_)const;
};

