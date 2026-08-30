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
	std::vector<ModelDescription::RenderState> allModelRenderStates =
		CollectAllRenderStates(modelContextDiplomat_);

	//全てのPassが入ってるコンテナを参照
	auto const& allPassPtrMap = passContainer_.AccessAllPassPtrMap(proof_);

	//PSO生成ツールを借りる
	auto* psoCOntextToolLender = pso_ContextDiplomat_.Access<PSO_Context::ToolLender>();
	PSO_Context::ToolLender::LicenceType<PSO_Context::PSO_Creator> usesPsoCreatorLicence;
	auto* psoCreator = psoCOntextToolLender->Lend<PSO_Context::PSO_Creator>(usesPsoCreatorLicence);

	//シェーダーライブラリを借りる
	auto* shaderContextToolLender = shaderContextDiplomat_.Access<ShaderContext::ToolLender>();
	ShaderContext::ToolLender::LicenceType<ShaderContext::ShaderLibrary> usesShaderLibLicence;
	auto* shaderLib = shaderContextToolLender->Lend<ShaderContext::ShaderLibrary>(usesShaderLibLicence);


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

		//そのPass専用のシェーダーファイル
		auto const& ms_psFile = passDesc.WatchMs_PsFileName();

		//それが存在していれば、モデルのどーたら関係なしにPSOを作成
		if (ms_psFile.has_value())
		{
			//PSO生成のためのディスク
			PipelineStateDesc::Graphics psoDesc;

			//使用するシェーダーファイルのバイナリデータのポインタ
			psoDesc.shaderSet.meshShader = shaderLib->Export(ms_psFile->first);
			psoDesc.shaderSet.meshShaderName = ms_psFile->first;
			//ピクセルシェーダーを通さないパターンもあるので"none"でチェックする
			if (ms_psFile->second != "none")
			{
				psoDesc.shaderSet.pixelShader = shaderLib->Export(ms_psFile->second);
				psoDesc.shaderSet.pixelShaderName = ms_psFile->second;
			}

		}
		//モデル描画パスなのでrenderStateの情報とともにPSOを作成
		else
		{
			//PipelineStateComponent::ShaderSet shaderSet;
			//PipelineStateComponent::RasterizerDesc rasterizerDesc;
			//PipelineStateComponent::RenderTargetDesc renderTargetDesc;
			//std::optional<PipelineStateComponent::DepthStencilDesc> depthStencilDesc;
			//PipelineStateComponent::SampleDesc sampleDesc;

		}
	}

	Logger::Entry("PSO creation end");

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

	//全てのモデルクラスのRenderStatesを集計
	const std::vector<std::unique_ptr<Model>>* modelDataContainer = watchModelContainer();

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
