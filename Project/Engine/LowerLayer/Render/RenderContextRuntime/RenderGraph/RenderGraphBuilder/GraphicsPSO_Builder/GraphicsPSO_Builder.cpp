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
	auto* psoContextToolLender = pso_ContextDiplomat_.Access<PSO_Context::ToolLender>();
	PSO_Context::ToolLender::LicenceType<PSO_Context::PSO_Creator> usesPsoCreatorLicence;
	auto* psoCreator = psoContextToolLender->Lend<PSO_Context::PSO_Creator>(usesPsoCreatorLicence);



	///これら二つのデータの塊からPSOを生成していく
	///基本は全Passを走査して、PassDescのms_ps(シェーダファイル)の有無で
	///renderStateとからめるかどうかを分岐させる
	///PSO = Pass X RenderState X FillMode
	Logger::Entry("PSO creation start");

	//全てのpsoディスク。ここに詰めていく
	std::vector<PipelineStateDesc::Graphics> allPsoDesc;

	for (UINT i = 0u; i < (UINT)Pass::kCount;++i)
	{
		//そのPassのDesc
		auto const& passDesc = allPassPtrMap.at(Pass(i))->WatchDesc();
		//パスの中身をログ出力。頼りはログのみ
		passDesc.DebugLog();

		//FillModeの個数分作る。ただしオフスクPassはWireFrameを用意する必要はないんで、
		//そこで分岐する
		for (UINT k = 0u;k < (UINT)RenderStateComponent::FillMode::kCount;++k)
		{
			//オフスクリーンパスでかつワイヤーフレームならスキップ
			if
			(
				passDesc.WatchMs_PsFileName().has_value() &&
				k == (UINT)RenderStateComponent::FillMode::kWireFrame
			) continue;


			///まずはオフスクリーン用かどうか関わらず、共通の設定を入力
			PipelineStateDesc::Graphics psoCommonDesc = InputCommonInfo(passDesc, RenderStateComponent::FillMode(k));

			///オフスクリーンパスであれば、renderPassの設定がPSOにダイレクトに反映
			InputPassOnlyInfo(shaderContextDiplomat_, psoCommonDesc, passDesc, allPsoDesc);

			///モデル描画パスであればモデルクラスの情報とパスの情報の二つで設定が決まる
			InputDependingModelsInfo
			(
				shaderContextDiplomat_,
				psoCommonDesc,
				passDesc,
				Pass(i),
				allModelRenderStates,
				allPsoDesc
			);

		}
	}

	std::string allPsoDescName = "= = = = All PSO List = = = = \n";

	//生成されたPSODescのデバッグ出力
	for (auto const& psoDesc : allPsoDesc)
	{
		allPsoDescName += psoDesc.psoName + "\n";
	}

	Logger::Log(allPsoDescName);

	Logger::Entry("PSO creation end");

}

PipelineStateDesc::Graphics RenderContext::RenderGraph::PSO_Builder::InputCommonInfo
(
	PassDesc const& passDesc_,
	RenderStateComponent::FillMode const fillMode_
)
{
	auto const& renderPassStates = passDesc_.WatchRenderPassState();
	auto const& depthStencilBufferInfo = passDesc_.WatchDepthStencilBufferInfo();

	PipelineStateDesc::Graphics psoCommon;

	//完全にPass依存
	{
		//ラスタライザー関係
		psoCommon.rasterizerDesc.depthBias = renderPassStates.depthBias;
		psoCommon.rasterizerDesc.depthBiasClamp = renderPassStates.depthBiasClamp;
		psoCommon.rasterizerDesc.slopeScaledDepthBias = renderPassStates.slopeScaledDepthBias;
		psoCommon.rasterizerDesc.fillMode = fillMode_;

		//深度設定
		psoCommon.depthStencilDesc.depthEnable = renderPassStates.depthEnable;
		psoCommon.depthStencilDesc.depthTest = renderPassStates.depthTest;

		//深度バッファの情報
		if (depthStencilBufferInfo.has_value())
		{
			psoCommon.depthStencilDesc.bufferName = depthStencilBufferInfo->bufferName;
			psoCommon.depthStencilDesc.clearDepth = depthStencilBufferInfo->clearDepth;
			psoCommon.depthStencilDesc.clearStencil = depthStencilBufferInfo->clearStencil;
			psoCommon.depthStencilDesc.dsvFormat = depthStencilBufferInfo->dsvFormat;
		}
		else
		{
			psoCommon.depthStencilDesc.doesUseBuffer = false;
		}

		//カラーバッファの情報
		auto const& colorBuffersInfo = passDesc_.WatchColorBuffersInfo();
		auto const numRenderTarget = colorBuffersInfo.size();
		psoCommon.renderTargetDescs.resize(numRenderTarget);
		for (size_t i = 0;i < numRenderTarget;++i)
		{
			auto& tmp = psoCommon.renderTargetDescs[i];

			tmp.bufferName = colorBuffersInfo[i].bufferName;
			tmp.rtvFormat = colorBuffersInfo[i].format;
		}		

		psoCommon.psoName += passDesc_.WatchName() + " X " + RenderStateComponent::FillModeToString(fillMode_);
	}

	return psoCommon;
}

//モデルクラスとレンダーパスの二つで残りのPSOの要素を定める
void RenderContext::RenderGraph::PSO_Builder::InputDependingModelsInfo
(
	ShaderContextDiplomat& shaderContextDiplomat_,
	PipelineStateDesc::Graphics& psoDescCommon_,
	PassDesc const& passDesc_,
	RenderPassComponent::Pass const renderPass_,
	std::vector<ModelDescription::RenderState> const& allRenderStates_,
	std::vector<PipelineStateDesc::Graphics>& allPsoDesc_

) 
{
	///レンダーパスがオフスクリーンで専用のシェーダーファイルを持って ” いなければ ”
	///それはモデル描画パス " である " 証拠
	if (passDesc_.WatchMs_PsFileName().has_value()) return;

	//シェーダーライブラリを借りる
	auto* shaderContextToolLender = shaderContextDiplomat_.Access<ShaderContext::ToolLender>();
	ShaderContext::ToolLender::LicenceType<ShaderContext::ShaderLibrary> usesShaderLibLicence;
	auto* shaderLib = shaderContextToolLender->Lend<ShaderContext::ShaderLibrary>(usesShaderLibLicence);

	///全renderState分ぶんまわす
	for (auto const& renderState : allRenderStates_)
	{
		///まず、そのrenderStateのパスと引数のパスが一致しているかチェックする
		///一致していない = そのモデルはそのパスで描画されない　のでPSOを作る必要がない
		if (renderState.pass != renderPass_) continue;


		//ブレンドモード以外は書き込んじゃう
		PipelineStateDesc::Graphics renderStateCommon(psoDescCommon_);
		{

			///使用するシェーダーはPass X MeshType , Pass X MaterialType で決まる
			std::string const msFileName = ShaderTable::GetMeshShader(renderPass_, renderState.meshType);
			std::string const psFileName = ShaderTable::GetPixelShader(renderPass_, renderState.materialType);

			//ファイル名からBlobのポインタを引っ張る
			renderStateCommon.shaderSet.meshShader = shaderLib->Export(msFileName);
			renderStateCommon.shaderSet.meshShaderName = msFileName;

			//ピクセルシェーダーを通さないケースもあるのでチェック
			if (psFileName != "none")
			{
				renderStateCommon.shaderSet.pixelShader = shaderLib->Export(psFileName);
				renderStateCommon.shaderSet.pixelShaderName = psFileName;
			}

			//ラスタライザー関連
			renderStateCommon.rasterizerDesc.cullMode = renderState.cullMode;

			renderStateCommon.psoName += " X " + renderState.modelName;
		}

		//blendModeはめんどいことに複数の可能性あり設計。その個数分ぶんまわす
		for (auto const& blendMode : renderState.blendModes)
		{
			//psoDescを一つずつ共通設定をコピーしてから、書き込んでいく
			PipelineStateDesc::Graphics psoDesc(renderStateCommon);

			//深度ステンシル関連
			psoDesc.depthStencilDesc.blendMode = blendMode;

			//レンダーターゲット関連
			for (auto& renderTargetDesc : psoDesc.renderTargetDescs)
			{
				//ブレンドモードはパスがモデル依存として設定しているかどうかで分岐させる
				if (renderTargetDesc.blendMode == RenderStateComponent::BlendMode::kDependsModel)
				{
					renderTargetDesc.blendMode = blendMode;
				}
			}

			psoDesc.psoName += " X " + RenderStateComponent::BlendModeToString(blendMode);

			//出来上がったディスクを回収
			allPsoDesc_.emplace_back(psoDesc);

		}
	}
}

//レンダーパスオンリーで残りのPSOの要素を定める
void RenderContext::RenderGraph::PSO_Builder::InputPassOnlyInfo
(
	ShaderContextDiplomat& shaderContextDiplomat_,
	PipelineStateDesc::Graphics const& psoCommonDesc_,
	PassDesc const& passDesc_,
	std::vector<PipelineStateDesc::Graphics>& allPsoDesc_
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

	//共通設定をコピー
	PipelineStateDesc::Graphics offscreenPassPsoDesc(psoCommonDesc_);

	//使用するシェーダーファイルのバイナリデータのポインタ
	offscreenPassPsoDesc.shaderSet.meshShader = shaderLib->Export(ms_psFile->first);
	offscreenPassPsoDesc.shaderSet.meshShaderName = ms_psFile->first;
	//ピクセルシェーダーを通さないパターンもあるので"none"でチェックする
	if (ms_psFile->second != "none")
	{
		offscreenPassPsoDesc.shaderSet.pixelShader = shaderLib->Export(ms_psFile->second);
		offscreenPassPsoDesc.shaderSet.pixelShaderName = ms_psFile->second;
	}

	//深度ステンシルのdepthWriteMaskの分岐に関わるもの。kOpaque固定
	offscreenPassPsoDesc.depthStencilDesc.blendMode = RenderStateComponent::BlendMode::kOpaque;
	
	//背面カリング固定
	offscreenPassPsoDesc.rasterizerDesc.cullMode = RenderStateComponent::CullMode::kBack;
	
	//レンダーターゲットの設定
	auto const& colorBuffersInfo = passDesc_.WatchColorBuffersInfo();
	size_t const numRT = colorBuffersInfo.size();
	for (size_t i = 0; i < numRT; ++i)
	{
		auto& tmp = offscreenPassPsoDesc.renderTargetDescs[i];

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

	offscreenPassPsoDesc.psoName += " X None(offScreen)";

	//出来上がったものを追加
	allPsoDesc_.emplace_back(offscreenPassPsoDesc);
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

	//モデルクラスを全走査し、全ModelDescriptionをかき集める
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
