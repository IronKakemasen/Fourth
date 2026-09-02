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

void RenderContext::RenderGraph::PSO_Builder::Build
(
	NexusFieldProof proof_,
	PSO_PoolDispatcher& psoDispatcher_,
	RenderPassContainer& passContainer_,
	ID3D12RootSignature* rootSignature_,
	ModelContextDiplomat& modelContextDiplomat_,
	PSO_ContextDiplomat& pso_ContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	//PSOのディスクを作って
	std::vector<PsoDesc_Key> allPSODesc =  CreateAllPSO_Desc
	(
		proof_,
		passContainer_,
		modelContextDiplomat_,
		shaderContextDiplomat_
	);

	//そのディスクをもとにpsoを生成
	CreateAllPSO(proof_, psoDispatcher_, allPSODesc, rootSignature_, pso_ContextDiplomat_);
}

void RenderContext::RenderGraph::PSO_Builder::CreateAllPSO
(
	NexusFieldProof proof_,
	PSO_PoolDispatcher& psoDispatcher_,
	std::vector<PsoDesc_Key>& allDesc_,
	ID3D12RootSignature* rootSignature_,
	PSO_ContextDiplomat& pso_ContextDiplomat_
)
{

	//PSO生成ツールを借りる
	auto* psoContextToolLender = pso_ContextDiplomat_.Access<PSO_Context::ToolLender>();
	PSO_Context::ToolLender::LicenceType<PSO_Context::PSO_Creator> usesPsoCreatorLicence;
	auto* psoCreator = psoContextToolLender->Lend<PSO_Context::PSO_Creator>(usesPsoCreatorLicence);

	for (auto& desc : allDesc_)
	{
		//PSO_PoolDispatcherで被りチェック
		//PSO_PoolDispatcherの検索Mapの開いている挿入スロット
		std::optional<uint32_t> dstInputSlot = psoDispatcher_.CheckDuplication(desc.second);

		//被ってたらスキップ
		if (!dstInputSlot.has_value())
		{
			Logger::Log(desc.first.psoName + " has Duplicated", fileName);
			continue;
		}
		//生成。本体はPSO_Context側が管理している。
		auto* psoPtr = psoCreator->Create(desc.first, rootSignature_, desc.first.psoName);

		//dispatcherにキーとともに登録
		psoDispatcher_.Register(proof_, *dstInputSlot, desc.second, psoPtr);

	}
}



std::vector<RenderContext::RenderGraph::PSO_Builder::PsoDesc_Key> RenderContext::RenderGraph::PSO_Builder::CreateAllPSO_Desc
(
	NexusFieldProof proof_,
	RenderPassContainer& passContainer_,
	ModelContextDiplomat& modelContextDiplomat_,
	ShaderContextDiplomat& shaderContextDiplomat_
)
{
	using namespace RenderPassComponent;

	//全てのモデルのRenderStatesを集計
	std::vector<ModelDescription::RenderState> allModelRenderStates = CollectAllRenderStates(modelContextDiplomat_);

	//全てのPassが入ってるコンテナを参照
	auto const& allPassPtrMap = passContainer_.AccessAllPassPtrMap(proof_);

	///これら二つのデータの塊からPSOを生成していく
	///基本は全Passを走査して、PassDescのms_ps(シェーダファイル)の有無で
	///renderStateとからめるかどうかを分岐させる
	///PSO = Pass X RenderState X FillMode

	//全てのpsoディスク(とキー)。ここに詰めていく
	std::vector<PsoDesc_Key> allPsoDesc;

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
			//共通設定が詰まったディスクとキーのセット
			PsoDesc_Key psoDesc_keyCommon = InputCommonInfo(Pass(i), passDesc, RenderStateComponent::FillMode(k));

			///オフスクリーンパスであれば、renderPassの設定がPSOにダイレクトに反映
			InputPassOnlyInfo(shaderContextDiplomat_, psoDesc_keyCommon, passDesc, allPsoDesc);

			///モデル描画パスであればモデルクラスの情報とパスの情報の二つで設定が決まる
			InputDependingModelsInfo
			(
				shaderContextDiplomat_,
				psoDesc_keyCommon,
				passDesc,
				Pass(i),
				allModelRenderStates,
				allPsoDesc
			);

		}
	}

	std::string allPsoDescName = "= = = = All PSO_Desc List = = = = \n";

	//生成されたPSODescのデバッグ出力
	for (auto const& psoDesc : allPsoDesc)
	{
		allPsoDescName += psoDesc.first.psoName + "\n";
	}

	Logger::Log(allPsoDescName);

	return allPsoDesc;


}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderContext::RenderGraph::PSO_Builder::PsoDesc_Key RenderContext::RenderGraph::PSO_Builder::InputCommonInfo
(
	RenderPassComponent::Pass const pass_,
	PassDesc const& passDesc_,
	RenderStateComponent::FillMode const fillMode_
)
{
	auto const& renderPassStates = passDesc_.WatchRenderPassState();
	auto const& depthStencilBufferInfo = passDesc_.WatchDepthStencilBufferInfo();

	PsoDesc_Key psoCommon;

	//完全にPass依存
	{
		//PSO_Keyの入力
		//フィルモード
		psoCommon.second.fill = fillMode_;
		psoCommon.second.pass = pass_;

		//ラスタライザー関係
		psoCommon.first.rasterizerDesc.depthBias = renderPassStates.depthBias;
		psoCommon.first.rasterizerDesc.depthBiasClamp = renderPassStates.depthBiasClamp;
		psoCommon.first.rasterizerDesc.slopeScaledDepthBias = renderPassStates.slopeScaledDepthBias;
		psoCommon.first.rasterizerDesc.fillMode = fillMode_;

		//深度設定
		psoCommon.first.depthStencilDesc.depthEnable = renderPassStates.depthEnable;
		psoCommon.first.depthStencilDesc.depthTest = renderPassStates.depthTest;

		//深度バッファの情報
		if (depthStencilBufferInfo.has_value())
		{
			psoCommon.first.depthStencilDesc.bufferName = depthStencilBufferInfo->bufferName;
			psoCommon.first.depthStencilDesc.clearDepth = depthStencilBufferInfo->clearDepth;
			psoCommon.first.depthStencilDesc.clearStencil = depthStencilBufferInfo->clearStencil;
			psoCommon.first.depthStencilDesc.dsvFormat = depthStencilBufferInfo->dsvFormat;
		}
		else
		{
			psoCommon.first.depthStencilDesc.doesUseBuffer = false;
		}

		//カラーバッファの情報
		auto const& colorBuffersInfo = passDesc_.WatchColorBuffersInfo();
		auto const numRenderTarget = colorBuffersInfo.size();
		psoCommon.first.renderTargetDescs.resize(numRenderTarget);
		for (size_t i = 0;i < numRenderTarget;++i)
		{
			auto& tmp = psoCommon.first.renderTargetDescs[i];

			tmp.bufferName = colorBuffersInfo[i].bufferName;
			tmp.rtvFormat = colorBuffersInfo[i].format;
		}		

		psoCommon.first.psoName += passDesc_.WatchName() + " X " + RenderStateComponent::FillModeToString(fillMode_);
	}

	return psoCommon;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//モデルクラスとレンダーパスの二つで残りのPSOの要素を定める
void RenderContext::RenderGraph::PSO_Builder::InputDependingModelsInfo
(
	ShaderContextDiplomat& shaderContextDiplomat_,
	PsoDesc_Key& psoCommonDesc_,
	PassDesc const& passDesc_,
	RenderPassComponent::Pass const renderPass_,
	std::vector<ModelDescription::RenderState> const& allRenderStates_,
	std::vector<PsoDesc_Key>& allPsoDesc_

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
		PsoDesc_Key renderStateCommon(psoCommonDesc_);
		{
			//PSO_Keyを入力
			renderStateCommon.second.mesh = renderState.meshType;
			renderStateCommon.second.material = renderState.materialType;
			renderStateCommon.second.cull = renderState.cullMode;

			///使用するシェーダーはPass X MeshType , Pass X MaterialType で決まる
			std::string const msFileName = ShaderTable::GetMeshShader(renderPass_, renderState.meshType);
			std::string const psFileName = ShaderTable::GetPixelShader(renderPass_, renderState.materialType);

			//ファイル名からBlobのポインタを引っ張る
			renderStateCommon.first.shaderSet.meshShader = shaderLib->Export(msFileName);
			renderStateCommon.first.shaderSet.meshShaderName = msFileName;

			//ピクセルシェーダーを通さないケースもあるのでチェック
			if (psFileName != "none")
			{
				renderStateCommon.first.shaderSet.pixelShader = shaderLib->Export(psFileName);
				renderStateCommon.first.shaderSet.pixelShaderName = psFileName;
			}

			//ラスタライザー関連
			renderStateCommon.first.rasterizerDesc.cullMode = renderState.cullMode;

			renderStateCommon.first.psoName += " X " + renderState.modelName;
		}

		//blendModeはめんどいことに複数の可能性あり設計。その個数分ぶんまわす
		for (auto const& blendMode : renderState.blendModes)
		{
			//psoDescを一つずつ共通設定をコピーしてから、書き込んでいく
			PsoDesc_Key psoDesc(renderStateCommon);

			//PSO_KeyにblendModeを入力
			psoDesc.second.blend = blendMode;

			//深度ステンシル関連
			psoDesc.first.depthStencilDesc.blendMode = blendMode;

			//レンダーターゲット関連
			for (auto& renderTargetDesc : psoDesc.first.renderTargetDescs)
			{
				//ブレンドモードはパスがモデル依存として設定しているかどうかで分岐させる
				if (renderTargetDesc.blendMode == RenderStateComponent::BlendMode::kDependsModel)
				{
					renderTargetDesc.blendMode = blendMode;
				}
			}

			psoDesc.first.psoName += " X " + RenderStateComponent::BlendModeToString(blendMode);

			//出来上がったディスクを回収
			allPsoDesc_.emplace_back(psoDesc);

		}
	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//レンダーパスオンリーで残りのPSOの要素を定める
void RenderContext::RenderGraph::PSO_Builder::InputPassOnlyInfo
(
	ShaderContextDiplomat& shaderContextDiplomat_,
	PsoDesc_Key& psoCommonDesc_,
	PassDesc const& passDesc_,
	std::vector<PsoDesc_Key>& allPsoDesc_
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
	PsoDesc_Key offscreenPassPsoDesc(psoCommonDesc_);

	//PSO_Keyのコンポーネントを入力
	//shaderPathComponentはどちらもoffscreen専用
	offscreenPassPsoDesc.second.mesh = ShaderPathComponent::MeshType::kOffscreen;
	offscreenPassPsoDesc.second.material = ShaderPathComponent::MaterialType::kOffscreen;
	offscreenPassPsoDesc.second.cull = RenderStateComponent::CullMode::kBack;
	///ここは悪影響が出るか分からんが、実際の各レンダーターゲットのブレンドモードの値は、
	///入力しているので恐らく問題ない。あくまでPSO_Keyのため
	offscreenPassPsoDesc.second.blend = RenderStateComponent::BlendMode::kOffScreen;

	//使用するシェーダーファイルのバイナリデータのポインタ
	offscreenPassPsoDesc.first.shaderSet.meshShader = shaderLib->Export(ms_psFile->first);
	offscreenPassPsoDesc.first.shaderSet.meshShaderName = ms_psFile->first;
	//ピクセルシェーダーを通さないパターンもあるので"none"でチェックする
	if (ms_psFile->second != "none")
	{
		offscreenPassPsoDesc.first.shaderSet.pixelShader = shaderLib->Export(ms_psFile->second);
		offscreenPassPsoDesc.first.shaderSet.pixelShaderName = ms_psFile->second;
	}

	//深度ステンシルのdepthWriteMaskの分岐に関わるもの。kOpaque固定
	offscreenPassPsoDesc.first.depthStencilDesc.blendMode = RenderStateComponent::BlendMode::kOpaque;
	
	//背面カリング固定
	offscreenPassPsoDesc.first.rasterizerDesc.cullMode = RenderStateComponent::CullMode::kBack;
	
	//レンダーターゲットの設定
	auto const& colorBuffersInfo = passDesc_.WatchColorBuffersInfo();
	size_t const numRT = colorBuffersInfo.size();
	for (size_t i = 0; i < numRT; ++i)
	{
		auto& tmp = offscreenPassPsoDesc.first.renderTargetDescs[i];

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

	offscreenPassPsoDesc.first.psoName += " X None(offScreen)";

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
