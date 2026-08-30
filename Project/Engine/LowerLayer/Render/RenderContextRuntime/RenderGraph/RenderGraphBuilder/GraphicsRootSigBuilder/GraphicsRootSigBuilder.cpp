#include "PreCompileHeader.h"
#include "GraphicsRootSigBuilder.h"


//外部
#include "../../../../../Resource/RootSignature/RootSigDiplomatIncludes.h"

namespace
{
	auto const fileName = "GraphicsRootSigBuilder.cpp";
}


[[nodiscard]] ID3D12RootSignature* RenderContext::RenderGraph::RootSigBuilder::CreateGraphicsRootSig
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
