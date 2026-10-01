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
	output.refBuffers = CreateAllPassInfo(proof_, renderPassCreator_, passContainer_, bufferContextDiplomat_);

	///パスが参照するバッファのsrvHeapIndexを詰めるためのバッファのID
	///UploadStructuredBufferでダブルです。中身の初期化もしていません
	output.targetFillInRefBufferID = CreateReferenceBufferSrvArray(proof_, output.refBuffers,bufferContextDiplomat_);

	//Passのルートコンスタンツのバッファを作成する
	CreatePassRootConstantsBuffer(proof_, bufferContextDiplomat_);

	return output;
}

std::vector<BufferUniqueID> RenderContext::StaticRenderGraph::PassSetUpper::CreateAllPassInfo
(
	NexusFieldProof proof_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//全てのPassが入ってるコンテナ
	auto const& allPassPtrMap = passContainer_.AccessAllPassPtrMap(proof_);
	//名前 :　パスのバッファのユニークID
	auto const& passBufferCache = renderPassCreator_.WatchPassBufferCache(proof_);
	
	//別メソッドで使用する、参照するバッファのsrvHeapIndex配列を作成するための素材
	std::vector<BufferUniqueID> allRefBufferUniques;
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
		UINT const refOffset = UINT(allRefBufferUniques.size());

		//そのパスが参照するバッファ一覧で回す
		std::vector<std::string> const& refBufferNames = desc.referenceBufferNames;
		//Passの参照先ばっふぁID格納用
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
				refColorBuffersID.emplace_back(refID);
			}
			else
			{
				refDepthStencilBuffersID.emplace_back(refID);
			}

			allRefBufferUniques.emplace_back(refID);
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


	return allRefBufferUniques;

}

SRVHeapIndex RenderContext::StaticRenderGraph::PassSetUpper::CreateReferenceBufferSrvArray
(
	NexusFieldProof proof_,
	std::vector<BufferUniqueID> const& data_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//グローバル定数バッファ生成コマンドをもらう
	auto cmdProv = bufferContextDiplomat_.Access<BufferContext::CmdProvider>();
	BufferContext::CmdProvider::LicenceType<BufferContextCmds::CreateCBufferCmd> licenceCmd;
	auto createCBufferCmd = cmdProv->Provide<BufferContextCmds::CreateCBufferCmd>(licenceCmd);
	
	//bufferCreatorを借りる
	auto toolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> licenceTool;
	auto* bufferCreator = toolLender->Lend<BufferContext::BufferCreator>(licenceTool);

	///バッファ作成
	std::string const bufferName = "RefBufSrvArr";
	UploadStructuredBufferDescription desc(UINT(sizeof(SRVHeapIndex)), UINT(data_.size()), 0);
	auto id_buffer = bufferCreator->CreateWithBuffer(desc, bufferName);

	//そのバッファのコンスタントバッファを生成し,
	auto cBufferID_cBuffer =
	createCBufferCmd(bufferName, UINT(sizeof(SRVHeapIndex)), (UINT)ConstantBuffers::ConstantBufferBindSlots::kPassRefBufferIndices);

	//srvHeapIndexを抽出しその定数バッファに記録
	cBufferID_cBuffer.second->WriteInBoth<SRVHeapIndex>
	(
		{ id_buffer.second->OutProperSRVHeapIndex(0),id_buffer.second->OutProperSRVHeapIndex(1) }
	);

	return id_buffer.first;
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
