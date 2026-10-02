#include "PreCompileHeader.h"
#include "PassSetUpper.h"
#include "../../../../RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "../../../../RenderPass/RenderPassCreator/RenderPassCreator.h"


//外部
#include "../../../../../Buffer/BufferContextToolsInclude.h"
#include "../../../../../Buffer/BufferContextCmds.h"
#include "../../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../../Buffer/BufferDefinition/AllBuffersInclude.h"
#include "../../../../../Buffer/BufferDefinition/AllBufferDescsInclude.h"

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

	///全てのパスが参照するバッファのIDが横一列に詰まっている
	///このIDを辿って、ランタイムの一歩目にsrvHeapIndexを詰めていく
	CreateAllPassInfo(proof_, output, renderPassCreator_, passContainer_, bufferContextDiplomat_);

	///パスが参照するバッファのsrvHeapIndexを詰めるためのバッファのID
	///UploadStructuredBufferでダブルです。中身の初期化もしていません
	CreateReferenceBufferSrvArray(proof_, output,bufferContextDiplomat_);

	//Passのルートコンスタンツのバッファを作成する
	CreatePassRootConstantsBuffer(proof_, bufferContextDiplomat_);

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
	//名前 :　パスのバッファのユニークID
	auto const& passBufferCache = renderPassCreator_.WatchPassBufferCache(proof_);
	
	//デバッグ用
	std::vector<std::string > allRefBufferNames;

	//bufferDispatcherを借りる
	auto toolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licenceTool;
	auto* bufferDispatcher = toolLender->Lend<BufferContext::BufferDispatcher>(licenceTool);

	//パスDescがどのバッファを使用するかの名前リストを所持しているので、それと組み合わせて埋めていく
	for (auto const& [kPassEnum, pass]: allPassPtrMap)
	{
		PassDesc const& desc = *pass->WatchDesc();
		std::string const& dsrPassName = desc.passName;

		//そのパスがバッファ配列の何番目を参照するか、であるPassBufferIndexRangeCPUGPUのoffset
		//普通にallRefBufferUniquesのけつ番目でいいはず
		UINT const refOffset = UINT(output_.refBufferTagTrace.size());

		//そのPassが参照するバッファ一覧で回す
		std::vector<std::string> const& refBufferNames = desc.referenceBufferNames;
		//そのPassの参照先ばっふぁID格納用
		std::vector<BufferUniqueID> refColorBuffersID;
		std::vector<BufferUniqueID> refDepthStencilBuffersID;

		for (auto const& refBufferName : refBufferNames)
		{
			//参照するバッファID
			//passCreatorが所持するidキャッシュから名前で引く
			BufferUniqueID refID = passBufferCache.at(refBufferName);

			//ここで参照先IDの指すバッファがカラーバッファなのか、深度バッファなのかで仕訳ける
			auto* buffer = bufferDispatcher->Dispatch(refID);

			if (dynamic_cast<ColorBuffer*>(buffer))
			{
				//参照先バッファをdynamicCastで確認して、何のバッファなのかTagを追加していく
				output_.refBufferTagTrace.emplace_back(ClassTraits<ColorBuffer>::kTag);
				//これはランタイムで使用する全パスの参照バッファ格納先(カラーバッファ)
				output_.refBuffersArr[(UINT)ClassTraits<ColorBuffer>::kTag].emplace_back(refID);

				//そのパスが参照するバッファIDの格納
				refColorBuffersID.emplace_back(refID);
			}
			else
			{
				//参照先バッファをdynamicCastで確認して、何のバッファなのかTagを追加していく
				output_.refBufferTagTrace.emplace_back(ClassTraits<DepthStencilBuffer>::kTag);
				//これはランタイムで使用する全パスの参照バッファ格納先(深度ステンシルバッファ)
				output_.refBuffersArr[(UINT)ClassTraits<DepthStencilBuffer>::kTag].emplace_back(refID);

				//そのパスが参照するバッファIDの格納
				refDepthStencilBuffersID.emplace_back(refID);
			}

			allRefBufferNames.emplace_back(refBufferName);
			
		}

		///PassDesc -> RuntimePassInfoに詰め変える
		pass->CreatePassInfo(proof_, refColorBuffersID , refDepthStencilBuffersID, refOffset);
		
	}

	//デバッグ表記
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


	///参照バッファ配列のバッファ作成
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
	id_buffer.second->WriteRange<SRVHeapIndex>
	(
		0,
		allRefIndices
	);

	//参照バッファ格納先のバッファIDを記録
	output_.targetFillInRefBufferID = id_buffer.first;

}


void RenderContext::StaticRenderGraph::PassSetUpper::CreatePassRootConstantsBuffer
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//グローバル定数バッファ生成コマンドをもらう
	auto cmdProv = bufferContextDiplomat_.Access<BufferContext::CmdProvider>();
	BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licence;
	auto createCBufferCmd = cmdProv->Provide<BufferContextCmds::CreateCBufferCmd>(licence);

	//ルートコンスタンツである、PassBufferIndexRangeCPUGPUの定数バッファ作成
	//もちろん中身はPassに依存するので、ドローコール時に書き込む
	createCBufferCmd("PassBufferIndexRange", UINT(sizeof(PassBufferIndexRangeCPUGPU)), (UINT)ConstantBuffers::RootConstantsBindSlots::kPassBufferIndexRange);

}
