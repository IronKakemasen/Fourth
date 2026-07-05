
#include "PSO_Assembler.h"


//ツール
#include "ToolCreatePSO/CreateBlendDesc/CreateBlendDesc.h"
#include "ToolCreatePSO/CreateDepthStencilDesc/CreateDepthStencilDesc.h"
#include "ToolCreatePSO/CreateRasterizerDesc/CreateRasterizerDesc.h"
#include "ToolCreatePSO/CreateSampleDesc/CreateSampleDesc.h"
#include "ToolCreatePSO/PSO_InfoOutputter/PSO_InfoOutputter.h"

namespace
{
	auto const fileName = "PSO_Assembler.cpp";
}

PSO_Context::Assembler::Assembler
(
	PSO_Context::InstanceKey key_,
	CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
	CommandCreateComputePSO cmdCreateComputePSO_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12PipelineState>>* psoContainer_
):cmdCreateGraphicsPSO(cmdCreateGraphicsPSO_), cmdCreateComputePSO(cmdCreateComputePSO_), psoContainer(psoContainer_)
{

}

PSO_Context::Assembler::~Assembler(){}

///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////

ID3D12PipelineState* PSO_Context::Assembler::AssembleGraphicsPSO
(
	PipelineStateDesc::Graphics& srcDesc_,	
	ID3D12RootSignature* rootSignature_,
	std::string debugName_
)
{
	Logger::Entry("assembling: " + debugName_);

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	//情報をデバッグ出力
	PSO_InfoOutputter outputter;
	outputter.OutputGraphicsPSOInfo
	(
		srcDesc_,	
		debugName_
	);


	//要項チェック
	Check(srcDesc_.shaderSet, srcDesc_.renderTargetDesc, debugName_);

	//使用するレンダーターゲットの数とそのフォーマットを入力
	CD3DX12_RT_FORMAT_ARRAY renderTargetFormatArray{};
	renderTargetFormatArray = SummarizeRenderTargetFormatInfo(srcDesc_.renderTargetDesc);

	//シェーダーバイトコードの生成
	MS_PS ms_ps = CreateShaderByteCode(srcDesc_.shaderSet);

	//ラスタライザー
	CD3DX12_RASTERIZER_DESC rasterizerDesc{};	
	{
		CreateRasterizerDesc creator;
		rasterizerDesc = creator.Create(srcDesc_.rasterizerDesc);
	}

	//ブレンドディスク
	CD3DX12_BLEND_DESC blendDesc{};
	{
		CreateBlendDesc creator;
		blendDesc = creator.Create(srcDesc_.renderTargetDesc);
	}

	//ディプスステンシルディスク
	CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc{};
	{
		CreateDepthStencilDesc creator;
		depthStencilDesc = creator.Create(srcDesc_.depthStencilDesc);
	}

	//サンプラーの設定
	DXGI_SAMPLE_DESC sampleDesc{};
	{
		CreateSampleDesc creator;
		sampleDesc = creator.Create(srcDesc_.sampleDesc);
	}

	PipelineStateDesc::MeshShaderPipelineStateStreamDesc pipelineDesc = {};
	D3D12_PIPELINE_STATE_STREAM_DESC streamDesc{};
	///集約
	{
		pipelineDesc.RTVFormats = renderTargetFormatArray;
		pipelineDesc.MS = ms_ps.first;
		if (ms_ps.second != std::nullopt)pipelineDesc.PS = *ms_ps.second;
		pipelineDesc.BlendState = blendDesc;
		pipelineDesc.DepthStencilState = depthStencilDesc;
		pipelineDesc.DSVFormat = srcDesc_.depthStencilDesc.dsvFormat;
		pipelineDesc.RasterizerState = rasterizerDesc;
		pipelineDesc.SampleDesc = sampleDesc;
		pipelineDesc.SampleMask = UINT_MAX;
		pipelineDesc.pRootSignature = rootSignature_;

		//全てをstreamDescに
		streamDesc.pPipelineStateSubobjectStream = &pipelineDesc;
		streamDesc.SizeInBytes = sizeof(pipelineDesc);
	}


	//コマンドで生成
	{
		cmdCreateGraphicsPSO(pipelineState.GetAddressOf(), &streamDesc);
	}

	Logger::End("assembling: " + debugName_);

	auto& dstPso = psoContainer->emplace_back(std::move(pipelineState));

	return dstPso.Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PSO_Context::Assembler::Check
(
	const PipelineStateDesc::ShaderSet& shaderSet_,
	const PipelineStateDesc::RenderTargetDesc& renderTargetDesc_,
	const std::string debugName_
)const
{
	std::string errorMsg = debugName_ + "\n";

	if (!shaderSet_.meshShader) errorMsg += "[MeshShaderがぬるぽ]";
	
	if(renderTargetDesc_.blendModeContainer.size() != renderTargetDesc_.rtvFormatContainer.size())
		errorMsg += "[renderTargetDescの不備]";


	ErrorMessageOutput::Assert::DetectError(errorMsg.size() == 0, errorMsg, fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CD3DX12_RT_FORMAT_ARRAY PSO_Context::Assembler::SummarizeRenderTargetFormatInfo(const PipelineStateDesc::RenderTargetDesc& renderTargetDesc_)const
{
	CD3DX12_RT_FORMAT_ARRAY renderTargetFormatArray = {};
	
	size_t const kNumRenderTargets = renderTargetDesc_.rtvFormatContainer.size();
	renderTargetFormatArray.NumRenderTargets = (UINT)renderTargetDesc_.rtvFormatContainer.size();

	for (size_t i = 0;i < kNumRenderTargets;++i) renderTargetFormatArray.RTFormats[i] = renderTargetDesc_.rtvFormatContainer[i];


	return renderTargetFormatArray;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PSO_Context::Assembler::MS_PS PSO_Context::Assembler::CreateShaderByteCode(PipelineStateDesc::ShaderSet& shaderSet_)
{
	MS_PS pair_byteCode;

	pair_byteCode.first =
	{
		shaderSet_.meshShader->GetBufferPointer(),
		shaderSet_.meshShader->GetBufferSize()
	};

	if (shaderSet_.pixelShader)
	{
		pair_byteCode.second =
		{
			shaderSet_.pixelShader->GetBufferPointer(),
			shaderSet_.pixelShader->GetBufferSize()
		};
	}
	else
	{
		pair_byteCode.second = std::nullopt;
	}

	return pair_byteCode;

}

