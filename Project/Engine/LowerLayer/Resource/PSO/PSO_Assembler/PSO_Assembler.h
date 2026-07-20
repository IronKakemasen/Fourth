#pragma once
#include "../PSO_Context.h"
#include "PipelineStateDesc.h"


class PSO_Context::Assembler
{

public:

	Assembler
	(
		PSO_Context::InstanceKey key_,
		DeviceContextDiplomat* deviceContextDiplomat_, 
		std::vector<Microsoft::WRL::ComPtr<ID3D12PipelineState>>* psoContainer_
	);

	~Assembler();

	ID3D12PipelineState* AssembleGraphicsPSO
	(
		PipelineStateDesc::Graphics& srcDesc_,
		ID3D12RootSignature* rootSignature_,
		std::string debugName_
	);


private:

	using MS_PS = std::pair<CD3DX12_SHADER_BYTECODE, std::optional<CD3DX12_SHADER_BYTECODE>>;

	//PSO生成コマンド
	CommandCreateGraphicsPSO cmdCreateGraphicsPSO;
	CommandCreateComputePSO cmdCreateComputePSO;

	//要項チェック
	void Check
	(
		const PipelineStateDesc::ShaderSet& shaderSet_,
		const PipelineStateDesc::RenderTargetDesc& renderTargetDesc_,
		const std::string debugName_
	)const;

	//レンダーターゲットのフォーマットと総数の情報をまとめる
	CD3DX12_RT_FORMAT_ARRAY SummarizeRenderTargetFormatInfo(const PipelineStateDesc::RenderTargetDesc& renderTargetDesc_)const;
	//シェーダーバイトコード作成
	MS_PS CreateShaderByteCode(PipelineStateDesc::ShaderSet& shaderSet_);

	std::vector<Microsoft::WRL::ComPtr<ID3D12PipelineState>>* psoContainer;

};

