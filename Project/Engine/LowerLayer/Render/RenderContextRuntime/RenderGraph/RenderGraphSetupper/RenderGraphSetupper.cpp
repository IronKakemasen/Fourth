#include "PreCompileHeader.h"
#include "RenderGraphSetupper.h"
#include "../../../RenderPath/RenderPathAssembler/RenderPathAssembler.h"
#include "../../PSO_PoolDispatcher/PSO_PoolDispatcher.h"
#include "../../../RenderPass/RenderPassContainer/RenderPassContainer.h"

//外部
#include "../../../../Resource/RootSignature/RootSignatureContextDiplomat/RootSignatureContextDiplomat.h"
#include "../../../../Resource/RootSignature/RootSignatureContextDiplomat/RootSignatureCmdProvider/RootSignatureCmdProvider.h"
#include "../../../../Resource/RootSignature/RootSignatureContextDiplomat/RootSignatureCmdProvider/RootSigCmdProviderLicences.h"
#include "../../../../Resource/RootSignature/RootSignatureCmds.h"

#include "../../../../Resource/Model/ModelContextDiplomat/ModelContextDiplomat.h"
#include "../../../../Resource/Model/ModelContextDiplomat/ModelContextCmdProvider/ModelContextCmdProvider.h"
#include "../../../../Resource/Model/ModelContextDiplomat/ModelContextCmdProvider/ModelContextCmdProviderLicences.h"
#include "../../../../Resource/Model/ModelContextCmds.h"
#include "../../../../Resource/Model/ModelStructure/Model.h"


namespace
{
	auto const fileName = "RenderGraphSetupper.cpp";
}

[[nodiscard]] AllPathPtr RenderContext::RenderGraph::Setupper::InstantiateAllPath
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	BufferContextDiplomat& bufferContextDiplomat_
) 
{
	AllPathPtr allPathPtr;

	std::get<CreateSceneTexture*>(allPathPtr) = pathAssembler_.Assemble<CreateSceneTexture>(proof_, bufferContextDiplomat_);
	Logger::Log("Create: CreateSceneTexture", fileName);


	return allPathPtr;
}

void RenderContext::RenderGraph::Setupper::CreateAllGraphicsPSO
(
	NexusFieldProof proof_,
	PSO_PoolDispatcher& psoDispatcher_, 
	RenderPassContainer& passContainer_,
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
	std::vector<ModelDescription::RenderState> allModelRenderStates = CollectAllRenderStates(modelDataContainer);

	//全てのPassが入ってるコンテナを参照
	auto const& allPassPtrMap = passContainer_.AccessAllPassPtrMap(proof_);

	///これら二つのデータの塊からPSOを生成していく
	
}

std::vector<ModelDescription::RenderState> RenderContext::RenderGraph::Setupper::CollectAllRenderStates
(
	const std::vector<std::unique_ptr<Model>>* modelData_
) 
{
	std::vector<ModelDescription::RenderState> allModelRenderStates;

	//モデルクラスを全走査し、全ModelDescriptionを見る
	for (auto itr = modelData_->begin();itr != modelData_->end();++itr)
	{
		//そのモデルクラスのModelDescのrenderStatesを回収
		for (auto const& renderState : (*itr)->WatchRenderStates())
		{
			allModelRenderStates.emplace_back(renderState);
		}
	}

	return allModelRenderStates;
}



[[nodiscard]] ID3D12RootSignature* RenderContext::RenderGraph::Setupper::CreateGraphicsRootSig
(
	NexusFieldProof proof_,
	RootSignatureContextDiplomat& rootSignatureContextDiplomat_
)
{
	using namespace RootSignatureLayoutComponent;
	using namespace StaticSampler;

	//rootSig生成コマンドをもらう
	auto* rootSigCmdProvider = rootSignatureContextDiplomat_.Access<RootSignatureContext::CmdProvider>();
	RootSignatureContext::CmdProvider::LicenceType<RootSignatureCmds::CreateGraphicsRootSigCmd> licenece;
	auto createRootSigCmd = rootSigCmdProvider->Provide<RootSignatureCmds::CreateGraphicsRootSigCmd>(licenece);

	RootSignatureDesc::Graphics desc;

	//とりあえずEnumで定義したある程度の静的サンプラーは全部作る
	for (int i = 0;i < (int)SamplerState::kCount;++i)
	{
		desc.pairshaderStage_samplerStateContainer.emplace_back(ShaderStage::kAll, SamplerState(i));
	}

	Logger::Log("Create: GraphicsRootSig", fileName);

	//ルートシグネチャを生成してそのポインタはもらっちゃう
	return createRootSigCmd(desc);
}
