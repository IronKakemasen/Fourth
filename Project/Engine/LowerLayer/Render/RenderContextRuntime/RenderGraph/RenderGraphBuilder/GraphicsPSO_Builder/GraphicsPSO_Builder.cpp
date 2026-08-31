#include "PreCompileHeader.h"
#include "GraphicsPSO_Builder.h"
#include "../../../PSO_PoolDispatcher/PSO_PoolDispatcher.h"
#include "../../../../RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "../../../../RenderPass/AllRenderPass/AllPassInclude.h"

#include "../../../../../Resource/Model/ModelContextDiplomat/ModelContextDiplomat.h"
#include "../../../../../Resource/Model/ModelContextDiplomat/ModelContextCmdProvider/ModelContextCmdProvider.h"
#include "../../../../../Resource/Model/ModelContextDiplomat/ModelContextCmdProvider/ModelContextCmdProviderLicences.h"
#include "../../../../../Resource/Model/ModelContextCmds.h"
#include "../../../../../Resource/Model/ModelStructure/Model.h"

#include "../../../../../Resource/PSO/PSO_ContextDiplomat/PSO_ContextDiplomat.h"
#include "../../../../../Resource/PSO/PSO_ContextDiplomat/PSO_ContextToolLender/PSO_ContextToolLender.h"
#include "../../../../../Resource/PSO/PSO_ContextDiplomat/PSO_ContextToolLender/PSO_ContextToolLenderLicences.h"
#include "../../../../../Resource/PSO/PSO_Creator/PSO_Creator.h"
		  
#include "../../../../../Resource/Shader/ShaderContextDiplomat/ShaderContextDiplomat.h"
#include "../../../../../Resource/Shader/ShaderContextDiplomat/ShaderContextToolLender/ShaderContextToolLender.h"
#include "../../../../../Resource/Shader/ShaderContextDiplomat/ShaderContextToolLender/ShaderContextToolLenderLicences.h"
#include "../../../../../Resource/Shader/ShaderLibrary/ShaderLibrary.h"
#include "../../../../../Resource/Shader/ShaderTable.h"


namespace
{
	auto const fileName = "GraphicsPSO_Builder.cpp";
}

void RenderContext::RenderGraph::PSO_Builder::CreateAllGraphicsPSO
(
	NexusFieldProof proof_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassContainer& passContainer_,
	ModelContextDiplomat& modelContextDiplomat_,
	PSO_ContextDiplomat& pso_ContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	using namespace RenderPassComponent;

	//全てのモデルのRenderStatesを集計
	std::vector<ModelDescription::RenderState> allModelRenderStates = CollectAllRenderStates(modelContextDiplomat_);

	//全てのPassが入ってるコンテナを参照
	auto const& allPassPtrMap = passContainer_.AccessAllPassPtrMap(proof_);

	//PSO生成ツールを借りる
	auto* psoCOntextToolLender = pso_ContextDiplomat_.Access<PSO_Context::ToolLender>();
	PSO_Context::ToolLender::LicenceType<PSO_Context::PSO_Creator> usesPsoCreatorLicence;
	auto* psoCreator = psoCOntextToolLender->Lend<PSO_Context::PSO_Creator>(usesPsoCreatorLicence);



	///これら二つのデータの塊からPSOを生成していく
	///全Passを捜査して、PassDescのms_ps(シェーダファイル)の有無でrenderStateと
	///からめるかどうかを分岐させる
	Logger::Entry("PSO creation start");

	for (UINT i = 0u; i < (UINT)Pass::kCount;++i)
	{
		//そのPassのDesc
		auto const& passDesc = allPassPtrMap.at(Pass(i))->WatchDesc();
		//パスの中身をログ出力。頼りはログのみ
		passDesc.DebugLog();

		//PSO生成のためのディスク
		PipelineStateDesc::Graphics psoDesc;

		///まずはオフスクリーン用かどうか関わらず、共通の設定
		InputCommonInfo(psoDesc, passDesc);

		///オフスクリーンパスであれば、renderPassの設定がPSOにダイレクトに反映
		InputPassOnlyInfo(shaderContextDiplomat_, psoDesc, passDesc);

		///モデル描画パスであればモデルクラスの情報とパスの情報の二つで設定が決まる
		auto const psoDescs = InputDependingModelsInfo
		(
			shaderContextDiplomat_,
			psoDesc,
			passDesc,
			Pass(i),
			allModelRenderStates
		);

	}

	Logger::Entry("PSO creation end");

}

void RenderContext::RenderGraph::PSO_Builder::InputCommonInfo
(
	PipelineStateDesc::Graphics& psoDesc_,
	PassDesc const& passDesc_
)
{
	auto const& renderStates = passDesc_.WatchRenderPassState();
	auto const& depthStencilBufferInfo = passDesc_.WatchDepthStencilBufferInfo();

	//完全にPass依存
	{
		//ラスタライザー関係
		psoDesc_.rasterizerDesc.depthBias = renderStates.depthBias;
		psoDesc_.rasterizerDesc.depthBiasClamp = renderStates.depthBiasClamp;
		psoDesc_.rasterizerDesc.slopeScaledDepthBias = renderStates.slopeScaledDepthBias;

		//深度設定
		psoDesc_.depthStencilDesc.depthEnable = renderStates.depthEnable;
		psoDesc_.depthStencilDesc.depthTest = renderStates.depthTest;

		//深度バッファの情報
		if (depthStencilBufferInfo.has_value())
		{
			psoDesc_.depthStencilDesc.bufferName = depthStencilBufferInfo->bufferName;
			psoDesc_.depthStencilDesc.clearDepth = depthStencilBufferInfo->clearDepth;
			psoDesc_.depthStencilDesc.clearStencil = depthStencilBufferInfo->clearStencil;
			psoDesc_.depthStencilDesc.dsvFormat = depthStencilBufferInfo->dsvFormat;
		}
		else
		{
			psoDesc_.depthStencilDesc.doesUseBuffer = false;
		}

		//カラーバッファの情報
		auto const& colorBuffersInfo = passDesc_.WatchColorBuffersInfo();
		auto const numRenderTarget = colorBuffersInfo.size();
		psoDesc_.renderTargetDescs.resize(numRenderTarget);
		for (size_t i = 0;i < numRenderTarget;++i)
		{
			auto& tmp = psoDesc_.renderTargetDescs[i];

			tmp.bufferName = colorBuffersInfo[i].bufferName;
			tmp.rtvFormat = colorBuffersInfo[i].format;
		}		
	}
}

//モデルクラスとレンダーパスの二つで残りのPSOの要素を定める
std::vector<PipelineStateDesc::Graphics> RenderContext::RenderGraph::PSO_Builder::InputDependingModelsInfo
(
	ShaderContextDiplomat& shaderContextDiplomat_,
	PipelineStateDesc::Graphics& psoDescCommon_,
	PassDesc const& passDesc_,
	RenderPassComponent::Pass const renderPass_,
	std::vector<ModelDescription::RenderState> const& allRenderStates_
) 
{
	std::vector<PipelineStateDesc::Graphics> psoDescs;

	///レンダーパスがオフスクリーンで専用のシェーダーファイルを持って ” いなければ ”
	///それはモデル描画パス " である " 証拠
	if (passDesc_.WatchMs_PsFileName().has_value()) return psoDescs;

	//シェーダーライブラリを借りる
	auto* shaderContextToolLender = shaderContextDiplomat_.Access<ShaderContext::ToolLender>();
	ShaderContext::ToolLender::LicenceType<ShaderContext::ShaderLibrary> usesShaderLibLicence;
	auto* shaderLib = shaderContextToolLender->Lend<ShaderContext::ShaderLibrary>(usesShaderLibLicence);

	psoDescs.assign(allRenderStates_.size(), psoDescCommon_);

	/////全renderState分ぶんまわす
	//for (auto const& renderState : allRenderStates_)
	//{
	//	renderState.
	//}

	/////使用するシェーダーはMeshType X Pass , MaterialType X Passで決まる
	//ShaderTable::GetMeshShader(renderPass_,)

	return psoDescs;
}

//レンダーパスオンリーで残りのPSOの要素を定める
void RenderContext::RenderGraph::PSO_Builder::InputPassOnlyInfo
(
	ShaderContextDiplomat& shaderContextDiplomat_,
	PipelineStateDesc::Graphics& psoDesc_,
	PassDesc const& passDesc_
) 
{
	///レンダーパスがオフスクリーンで専用のシェーダーファイルを持って ” いれば ”
	///それはモデル描画パス " でない " 証拠
	if (!passDesc_.WatchMs_PsFileName().has_value()) return;

	//シェーダーライブラリを借りる
	auto* shaderContextToolLender = shaderContextDiplomat_.Access<ShaderContext::ToolLender>();
	ShaderContext::ToolLender::LicenceType<ShaderContext::ShaderLibrary> usesShaderLibLicence;
	auto* shaderLib = shaderContextToolLender->Lend<ShaderContext::ShaderLibrary>(usesShaderLibLicence);

	//そのPass専用のシェーダーファイル(Optional)
	auto const& ms_psFile = passDesc_.WatchMs_PsFileName();

	//使用するシェーダーファイルのバイナリデータのポインタ
	psoDesc_.shaderSet.meshShader = shaderLib->Export(ms_psFile->first);
	psoDesc_.shaderSet.meshShaderName = ms_psFile->first;
	//ピクセルシェーダーを通さないパターンもあるので"none"でチェックする
	if (ms_psFile->second != "none")
	{
		psoDesc_.shaderSet.pixelShader = shaderLib->Export(ms_psFile->second);
		psoDesc_.shaderSet.pixelShaderName = ms_psFile->second;
	}

	//深度ステンシルのdepthWriteMaskの分岐に関わるもの。kOpaque固定
	psoDesc_.depthStencilDesc.blendMode = RenderStateComponent::BlendMode::kOpaque;
	
	//背面カリング固定
	psoDesc_.rasterizerDesc.cullMode = RenderStateComponent::CullMode::kBack;
	
	//レンダーターゲットの設定
	auto const& colorBuffersInfo = passDesc_.WatchColorBuffersInfo();
	size_t const numRT = colorBuffersInfo.size();
	for (size_t i = 0; i < numRT; ++i)
	{
		auto& tmp = psoDesc_.renderTargetDescs[i];

		//ここでcolorBuffersInfoのブレンドモードがkDependsModelだとおかしい
		ErrorMessageOutput::Assert::DetectError
		(
			colorBuffersInfo[i].blendMode != RenderStateComponent::BlendMode::kDependsModel,
			passDesc_.WatchName() + "はオフスクリーンパスなのにブレンドモードがkDependsModel",
			fileName
		);

		//パス固定のブレンドモードを詰めていく
		tmp.blendMode = colorBuffersInfo[i].blendMode;
	}	
}


std::vector<ModelDescription::RenderState> RenderContext::RenderGraph::PSO_Builder::CollectAllRenderStates
(
	ModelContextDiplomat& modelContextDiplomat_
)
{
	using namespace ModelContextCmds;

	//モデルコンテナの中身を覗くコマンドをもらう
	auto* modelContextCmdProvider = modelContextDiplomat_.Access<ModelContext::CommandProvider>();
	ModelContext::CommandProvider::LicenceType<WatchModelContainer> licence;
	auto watchModelContainer = modelContextCmdProvider->Provide<WatchModelContainer>(licence);

	//全てのモデルクラスのコンテナ
	const std::vector<std::unique_ptr<Model>>* modelDataContainer = watchModelContainer();
	//全てのモデルクラスのRenderStates
	std::vector<ModelDescription::RenderState> allModelRenderStates;

	//モデルクラスを全走査し、全ModelDescriptionを見る
	for (auto itr = modelDataContainer->begin();itr != modelDataContainer->end();++itr)
	{
		//そのモデルクラスのModelDescのrenderStatesを回収
		for (auto const& renderState : (*itr)->WatchRenderStates())
		{
			allModelRenderStates.emplace_back(renderState);
		}
	}

	return allModelRenderStates;
}
