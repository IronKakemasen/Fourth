#pragma once
#include "../../PSO_Context.h"
#include "../PipelineStateDesc.h"


class PSO_Context::Assembler
{

public:

	struct Local_AssembleLicence;

	Assembler
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_
	);

	~Assembler();

	template<typename DescType>
	Microsoft::WRL::ComPtr<ID3D12PipelineState> Assemble
	(
		Local_AssembleLicence licence_,
		DescType& srcDesc_,
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
		const PipelineStateComponent::ShaderSet& shaderSet_,
		const std::vector<PipelineStateComponent::RenderTargetDesc>& renderTargetDescs_,
		const std::string debugName_
	)const;

	//レンダーターゲットのフォーマットと総数の情報をまとめる
	CD3DX12_RT_FORMAT_ARRAY SummarizeRenderTargetFormatInfo
	(const std::vector<PipelineStateComponent::RenderTargetDesc>& renderTargetDescs_)const;
	//シェーダーバイトコード作成
	MS_PS CreateShaderByteCode(PipelineStateComponent::ShaderSet& shaderSet_);

};

struct PSO_Context::Assembler::Local_AssembleLicence
{
private:

	friend class PSO_Creator;
	explicit Local_AssembleLicence() = default;
};



template<>
Microsoft::WRL::ComPtr<ID3D12PipelineState> PSO_Context::Assembler::Assemble
(
	Local_AssembleLicence licence_,
	PipelineStateDesc::Graphics& srcDesc_,
	ID3D12RootSignature* rootSignature_,
	std::string debugName_
);



