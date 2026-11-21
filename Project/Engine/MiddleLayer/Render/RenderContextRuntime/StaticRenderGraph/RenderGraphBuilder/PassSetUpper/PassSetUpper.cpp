#include "PreCompileHeader.h"
#include "PassSetUpper.h"
#include "../../../../RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "../../../../RenderPass/RenderPassCreator/RenderPassCreator.h"


//外部
#include "../../../../../../LowerLayer/Buffer/BufferContextToolsInclude.h"
#include "../../../../../../LowerLayer/Buffer/BufferContextCmds.h"
#include "../../../../../../LowerLayer/Buffer/BufferContextDiplomats.h"
#include "../../../../../../LowerLayer/Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../../../../LowerLayer/Buffer/BufferDefinition/AllBufferDescsInclude.h"

#include "../../../../../../../Assets/Shared/ConstantBuffers.h"

using namespace ConstantBuffers;
using namespace BufferTraits;

namespace
{
	auto const fileName = "PassSetUpper.cpp";
}

[[nodiscard]] RenderContext::StaticRenderGraph::BuildOutput::PassSetUpper RenderContext::StaticRenderGraph::PassSetUpper::Setup
(
	NexusFieldProof proof_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	BuildOutput::PassSetUpper output;

	//パスの参照バッファ、書き込みシェアバッファをPassDescから詰めていく
	//そして、PassDescをもとにRuntimePassInfoを作成する
	CreateAllPassInfo(proof_, output, renderPassCreator_, passContainer_, bufferContextDiplomat_);
	Logger::Log("Create All PassInfo", fileName);

	//参照バッファのsrv配列のバッファを作成する
	CreateReferenceBufferSrvArray(proof_, output,bufferContextDiplomat_);
	Logger::Log("Create ReferenceBufferSrvArray", fileName);

	//最終パス(フロントバッファを描画)で参照するカラーバッファを詰める
	SetFinalColorBuffer(proof_, output, renderPassCreator_);
	Logger::Log("Set Final Pass RefColorBuffer", fileName);

	return output;
}

void RenderContext::StaticRenderGraph::PassSetUpper::CreateAllPassInfo
(
	NexusFieldProof proof_,
	BuildOutput::PassSetUpper& output_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//全てのPassが入ってるコンテナ
	auto const& allPassPtrMap = passContainer_.AccessAllPassPtrMap(proof_);

	//参照先バッファの名前一覧デバッグ用。並び順が重要なので
	std::vector<std::string > allRefBufferNames;

	//パスDescがどのバッファを使用するかの名前リストを所持しているので、それと組み合わせて埋めていく
	for (auto const& [kPassEnum, pass]: allPassPtrMap)
	{
		//各パスの書き込み共有バッファをバッファ名から埋めていく
		AddWriteSharingBuffer(proof_, *pass, renderPassCreator_);

		//パスの参照バッファを追加し、desc -> runtimePassInfoへ情報を詰める
		//後にパスの参照先バッファID群のバッファ作成のために必要になるため、
		//パスの参照バッファIDを記録しておく
		AddRefBufferFuncReturn addRefBufferFuncReturn = AddRefBuffer
		(
			proof_,
			*pass,
			output_,
			renderPassCreator_,
			allRefBufferNames,
			bufferContextDiplomat_
		);

		//RuntimePassInfoを作成する
		CreateRuntimePassInfo(proof_, *pass, std::move(addRefBufferFuncReturn));
	}

#ifdef  _DEBUG

	Logger::Log("- - - - - All Pass Reference Buffers - - - - - ", fileName);
	std::string log = "\nallRefBufferNames: ";
	int cnt= 1;
	for (auto const& v : allRefBufferNames)
	{
		log += v + ",";
		cnt % 5 == 0 ? log += "\n" : log += "";
	}

	log += "\n";
	Logger::Log(log);

	Logger::Log("- - - - - - - - - - - - - - - - - - - - ", fileName);

#endif //  _DEBUG

}

RenderContext::StaticRenderGraph::PassSetUpper::AddRefBufferFuncReturn RenderContext::StaticRenderGraph::PassSetUpper::AddRefBuffer
(
	NexusFieldProof proof_,
	PassBehavior& pass_,
	BuildOutput::PassSetUpper& output_,
	RenderPassCreator& renderPassCreator_,
	[[maybe_unused]] std::vector<std::string >& debug_allRefBufferNames_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//bufferDispatcherを借りる
	auto toolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licenceTool;
	auto* bufferDispatcher = toolLender->Lend<BufferContext::BufferDispatcher>(licenceTool);

	//名前 :　パスのバッファのユニークID
	auto const& passBufferCache = renderPassCreator_.WatchPassBufferCache(proof_);

	//パスのディスク
	PassDesc& desc = pass_.RefPassDesc(proof_);

	AddRefBufferFuncReturn addRefBufferFuncReturn;
	//パスの所持する、参照バッファ配列のオフセット
	addRefBufferFuncReturn.refOffset = UINT(output_.refBufferTagTrace.size());

	//そのPassが参照するバッファ一覧で回す
	std::vector<std::string> const& refBufferNames = desc.referenceBufferNames;

	for (auto const& refBufferName : refBufferNames)
	{
		//参照するバッファID
		//passCreatorが所持するidキャッシュから名前で引く
		BufferUniqueID refID = passBufferCache.at(refBufferName);

		//ここで参照先IDの指すバッファがカラーバッファなのか、深度バッファなのかで
		auto* buffer = bufferDispatcher->Dispatch(refID);

		if (dynamic_cast<ColorBuffer*>(buffer))
		{
			//参照先バッファをdynamicCastで確認して、何のバッファなのかTagを追加していく
			output_.refBufferTagTrace.emplace_back(ClassTraits<ColorBuffer>::kTag);
			//これはランタイムで使用する全パスの参照バッファ格納先(カラーバッファ)
			output_.refBuffersArr[(UINT)ClassTraits<ColorBuffer>::kTag].emplace_back(refID);

			//そのパスが参照するバッファIDの格納
			addRefBufferFuncReturn.refColorBuffersID.emplace_back(refID);
		}
		else
		{
			//参照先バッファをdynamicCastで確認して、何のバッファなのかTagを追加していく
			output_.refBufferTagTrace.emplace_back(ClassTraits<DepthStencilBuffer>::kTag);
			//これはランタイムで使用する全パスの参照バッファ格納先(深度ステンシルバッファ)
			output_.refBuffersArr[(UINT)ClassTraits<DepthStencilBuffer>::kTag].emplace_back(refID);

			//そのパスが参照するバッファIDの格納
			addRefBufferFuncReturn.refDepthStencilBuffersID.emplace_back(refID);
		}
#ifdef _DEBUG

		//名前確認デバッグ用
		debug_allRefBufferNames_.emplace_back(refBufferName);

#endif // _DEBUG

	}

	return addRefBufferFuncReturn;
}

void RenderContext::StaticRenderGraph::PassSetUpper::CreateRuntimePassInfo
(
	NexusFieldProof proof_,
	PassBehavior& pass_,
	AddRefBufferFuncReturn addRefBufferFuncReturn_
)
{
	//RuntimePassInfoを作成する
	pass_.CreatePassInfo(proof_, addRefBufferFuncReturn_.refColorBuffersID, addRefBufferFuncReturn_.refDepthStencilBuffersID, addRefBufferFuncReturn_.refOffset);
}

void RenderContext::StaticRenderGraph::PassSetUpper::AddWriteSharingBuffer
(
	NexusFieldProof proof_,
	PassBehavior& pass_,
	RenderPassCreator& renderPassCreator_
)
{
	//書き込みシェアバッファ取り付けのためのキャッシュ
	auto const& colorBufferInfoMapCache = renderPassCreator_.WatchColorBufferInfoMapCache(proof_);
	auto const& depthBufferInfoMapCache = renderPassCreator_.WatchDepthBufferInfoMapCache(proof_);

	PassDesc& desc = pass_.RefPassDesc(proof_);

	//書き込みシェアするバッファの追加(ColorBuffer)
	for (auto const& name : desc.writeSharingColorBufferNames)
	{
		//検索
		RequiredBufferInfo::ColorBuffer colorBufferinfo = *colorBufferInfoMapCache.at(name);
		//自前バッファでなければクリアしない
		colorBufferinfo.doClear = false;

		//書き込むので自前バッファとして追加
		desc.colorBuffersInfo.emplace_back(colorBufferinfo);
	}

	//書き込みシェアするバッファの追加(DepthBuffer)
	std::string const& depthBufferInfoName = desc.writeSharingDepthBufferName;
	if (depthBufferInfoName.size() > 0)
	{
		RequiredBufferInfo::DepthStencilBuffer depthBufferinfo = *depthBufferInfoMapCache.at(depthBufferInfoName);
		depthBufferinfo.doClear = false;

		desc.depthStencilBufferInfo = depthBufferinfo;
	}
}

void RenderContext::StaticRenderGraph::PassSetUpper::SetFinalColorBuffer
(
	NexusFieldProof proof_,
	BuildOutput::PassSetUpper& output_,
	RenderPassCreator& renderPassCreator_
)
{
	//名前 :　パスのバッファのユニークID
	auto const& passBufferCache = renderPassCreator_.WatchPassBufferCache(proof_);

	//フロントバッファ参照カラーバッファの名前をjsonfileから取得
	Miyajison* miyajison = Miyajison::Get();
	auto const finalColorBufferName = miyajison->LoadData<std::string>(DataKey::kRenderGraphSettings, { DataKey::kFinalColorBuffer });
	//最終カラーバッファと名前が一致しているカラーバッファのIDを格納
	output_.finalColorBufferID = passBufferCache.at(finalColorBufferName);
}


void RenderContext::StaticRenderGraph::PassSetUpper::CreateReferenceBufferSrvArray
(
	NexusFieldProof proof_,
	BuildOutput::PassSetUpper& output_, 
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//グローバル定数バッファ生成コマンドをもらう
	auto cmdProv = bufferContextDiplomat_.Access<BufferContext::CmdProvider>();
	BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licenceCmd;
	auto createCBufferCmd = cmdProv->Provide<BufferContextCmds::CreateCBufferCmd>(licenceCmd);
	
	//bufferCreatorとbufferDispatcherを借りる
	auto toolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licenceTool;
	auto* bufferCreator = toolLender->Lend<BufferContext::BufferCreator>(licenceTool);
	auto* bufferDispatcher = toolLender->Lend<BufferContext::BufferDispatcher>(licenceTool);


	///参照バッファ配列の定数バッファ作成
	std::string const bufferName = "RefBufSrvArr";
	UploadStructuredBufferDescription desc(UINT(sizeof(SRVHeapIndex)), UINT(output_.refBufferTagTrace.size()), 0);
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, bufferName);

	//そのバッファのコンスタントバッファを生成し,
	auto cBufferID_cBuffer =
	createCBufferCmd(bufferName, UINT(sizeof(SRVHeapIndex)), (UINT)ConstantBuffers::ConstantBufferBindSlots::kPassRefBufferIndices);

	//srvHeapIndexを抽出しその定数バッファに記録
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ id_buffer.second->OutProperSRVHeapIndex(0),id_buffer.second->OutProperSRVHeapIndex(1) }
	);

	//参照バッファ配列のバッファにも初期値を書き込んでおく
	std::vector<SRVHeapIndex> allRefIndices;
	allRefIndices.reserve(output_.refBufferTagTrace.size());
	std::array<UINT, BuildOutput::PassSetUpper::kNumRefBufferType > indexCnts{};

	for (auto const bufferTag : output_.refBufferTagTrace)
	{
		//参照バッファがどっちかをインデックスに
		UINT const bufferTypeIndex = UINT(bufferTag);

		//参照バッファのID　→　バッファ　→　srvHeapIndex
		BufferUniqueID refID = output_.refBuffersArr[bufferTypeIndex][indexCnts[bufferTypeIndex]++];
		auto* refbuffer = bufferDispatcher->Dispatch(refID);
		SRVHeapIndex refSrvIndex{};

		if (bufferTag == BufferTag::kColor)
		{
			refSrvIndex = static_cast<ColorBuffer*>(refbuffer)->OutProperSRVHeapIndex();
		}
		else
		{
			refSrvIndex = static_cast<DepthStencilBuffer*>(refbuffer)->OutProperSRVHeapIndex();
		}

		allRefIndices.emplace_back(refSrvIndex);
	}

	//初期フレーム分を「0」に入力。初手フレームインデックスは0。つまり、書き込むべきは0
	//読み込むべきは1
	//と言いたいところだがいちおう両方に入力しておく
	id_buffer.second->WriteRangeInBoth<SRVHeapIndex>
	(
		{ allRefIndices,allRefIndices }
	);

	//参照バッファ格納先のバッファIDを記録
	output_.targetFillInRefBufferID = id_buffer.first;

}


