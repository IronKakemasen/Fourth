#include "PreCompileHeader.h"
#include "PassSetUpper.h"
#include "../../../../RenderPass/RenderPassContainer/RenderPassContainer.h"
#include "../../../../RenderPass/RenderPassCreator/RenderPassCreator.h"


//外部
#include "../../../../../Buffer/BufferContextToolsInclude.h"
#include "../../../../../Buffer/BufferContextCmds.h"
#include "../../../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../../../Buffer/BufferContextDiplomat/BufferContextCmdProvider/BufferContextCmdProvider.h"
#include "../../../../../Buffer/BufferContextDiplomat/BufferContextCmdProvider/BufferContextCmdProviderLicences.h"

#include "../../../../../../../Assets/Shared/ConstantBuffers.h"

using namespace ConstantBuffers;

namespace
{
	auto const fileName = "PassSetUpper.cpp";
}

void RenderContext::RenderGraph::PassSetUpper::Setup
(
	NexusFieldProof proof_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{

	std::vector<BufferUniqueID> allRefBuffer = CreateAllPassInfo(proof_, renderPassCreator_, passContainer_);

	CreatePassRootConstantsBuffer(proof_, bufferContextDiplomat_);

}

std::vector<BufferUniqueID> RenderContext::RenderGraph::PassSetUpper::CreateAllPassInfo
(
	NexusFieldProof proof_,
	RenderPassCreator& renderPassCreator_,
	RenderPassContainer& passContainer_
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


	//パス自身がどのバッファを使用するかの名前リストを所持しているので、それと組み合わせて埋めていく
	for (auto const& [passEnum, pass]: allPassPtrMap)
	{
		PassDesc const& desc = *pass->WatchDesc();
		std::string const dsrPassName = desc.passName;

		//そのパスがバッファ配列の何番目を参照するか、であるPassBufferIndexRangeCPUGPUのoffset
		//普通にallRefBufferUniquesのけつ番目でいいはず
		UINT const refOffset = UINT(allRefBufferUniques.size());

		//参照するバッファ一覧で回す
		std::vector<std::string> const& refBufferNames = desc.referenceBufferNames;
		std::unordered_map<std::string, BufferUniqueID> idMap;

		for (auto const refBufferName : refBufferNames)
		{
			//参照するバッファID
			BufferUniqueID refID = passBufferCache.at(refBufferName);

			idMap[refBufferName] = refID;
			allRefBufferUniques.emplace_back(refID);
			allRefBufferNames.emplace_back(refBufferName);
		}

		///PassDesc -> RuntimePassInfoに詰め変える
		pass->CreatePassInfo(proof_, idMap, refOffset);
		
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


void RenderContext::RenderGraph::PassSetUpper::CreatePassRootConstantsBuffer
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
