#include "PreCompileHeader.h"
#include "PSO_Assembler.h"


//ツール
#include "ToolCreatePSO/CreateBlendDesc/CreateBlendDesc.h"
#include "ToolCreatePSO/CreateDepthStencilDesc/CreateDepthStencilDesc.h"
#include "ToolCreatePSO/CreateRasterizerDesc/CreateRasterizerDesc.h"
#include "ToolCreatePSO/CreateSampleDesc/CreateSampleDesc.h"


namespace
{
	auto const fileName = "PSO_Assembler.cpp";
}

PSO_Context::Assembler::Assembler
(
	PSO_Context::InstanceKey key_,
	CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
	CommandCreateComputePSO cmdCreateComputePSO_
):cmdCreateGraphicsPSO(cmdCreateGraphicsPSO_), cmdCreateComputePSO(cmdCreateComputePSO_)
{
	
}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////

Microsoft::WRL::ComPtr<ID3D12PipelineState> PSO_Context::Assembler::AssembleGraphicsPSO
(
	PipelineStateDesc::ShaderSet shaderSet_,
	PipelineStateDesc::RenderTargetDesc renderTargetDesc_,
	PipelineStateDesc::RasterizerDesc rasterizerDesc_,
	PipelineStateDesc::DepthStencilDesc depthStencilDesc_,
	PipelineStateDesc::SampleDesc sampleDesc_,
	ID3D12RootSignature* rootSignature_
)
{
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	//要項チェック
	Check(shaderSet_, renderTargetDesc_);


	///==========================================================================================================
	//使用するレンダーターゲットの数とそのフォーマットを入力
	CD3DX12_RT_FORMAT_ARRAY renderTargetFormatArray = {};
	{
		size_t const kNumRenderTargets = renderTargetDesc_.rtvFormatContainer.size();
		renderTargetFormatArray.NumRenderTargets = (UINT)renderTargetDesc_.rtvFormatContainer.size();
		for (size_t i = 0;i < kNumRenderTargets;++i) renderTargetFormatArray.RTFormats[i] = renderTargetDesc_.rtvFormatContainer[i];
	}
	///==========================================================================================================


	///==========================================================================================================
	//シェーダーのセット
	CD3DX12_SHADER_BYTECODE ms{};
	CD3DX12_SHADER_BYTECODE ps{};
	{
		ms = 
		{
			shaderSet_.meshShader->GetBufferPointer(),
			shaderSet_.meshShader->GetBufferSize()
		};

		if (shaderSet_.pixelShader)
		{
			ps =
			{
				shaderSet_.pixelShader->GetBufferPointer(),
				shaderSet_.pixelShader->GetBufferSize()
			};
		}
	}
	///==========================================================================================================


	///==========================================================================================================
	//ラスタライザー
	CD3DX12_RASTERIZER_DESC rasterizerDesc{};	
	{
		CreateRasterizerDesc creator;
		rasterizerDesc = creator.Create(rasterizerDesc_);
	}
	///==========================================================================================================


	///==========================================================================================================
	//ブレンドディスク
	CD3DX12_BLEND_DESC blendDesc{};
	{
		CreateBlendDesc creator;
		blendDesc = creator.Create(renderTargetDesc_);
	}
	///==========================================================================================================


	///==========================================================================================================
	//ディプスステンシルディスク
	CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc{};
	{
		CreateDepthStencilDesc creator;
		depthStencilDesc = creator.Create(depthStencilDesc_);
	}
	///==========================================================================================================


	///==========================================================================================================
	//サンプラーの設定
	DXGI_SAMPLE_DESC sampleDesc{};
	{
		CreateSampleDesc creator;
		sampleDesc = creator.Create(sampleDesc_);
	}
	///==========================================================================================================


	///==========================================================================================================
	PipelineStateDesc::MeshShaderPipelineStateStreamDesc pipelineDesc = {};
	D3D12_PIPELINE_STATE_STREAM_DESC streamDesc{};
	///集約
	{
		pipelineDesc.RTVFormats = renderTargetFormatArray;
		pipelineDesc.MS = ms;
		pipelineDesc.PS = ps;
		pipelineDesc.BlendState = blendDesc;
		pipelineDesc.DepthStencilState = depthStencilDesc;
		pipelineDesc.DSVFormat = depthStencilDesc_.dsvFormat;
		pipelineDesc.RasterizerState = rasterizerDesc;
		pipelineDesc.SampleDesc = sampleDesc;
		pipelineDesc.SampleMask = UINT_MAX;
		pipelineDesc.pRootSignature = rootSignature_;

		//全てをstreamDescに
		streamDesc.pPipelineStateSubobjectStream = &pipelineDesc;
		streamDesc.SizeInBytes = sizeof(pipelineDesc);
	}
	///==========================================================================================================


	//コマンドで生成
	{
		cmdCreateGraphicsPSO(pipelineState.GetAddressOf(), &streamDesc);
	}


	return pipelineState;
}

void PSO_Context::Assembler::Check(const PipelineStateDesc::ShaderSet& shaderSet_, const PipelineStateDesc::RenderTargetDesc& renderTargetDesc_)const
{
	ErrorMessageOutput::Assert::DetectError((shaderSet_.meshShader), "MeshSHaderがぬるぽ", fileName);
	ErrorMessageOutput::Assert::DetectError
	(
		renderTargetDesc_.blendModeContainer.size() == renderTargetDesc_.rtvFormatContainer.size(),
		"renderTargetDescの不備",
		fileName
	);

}
