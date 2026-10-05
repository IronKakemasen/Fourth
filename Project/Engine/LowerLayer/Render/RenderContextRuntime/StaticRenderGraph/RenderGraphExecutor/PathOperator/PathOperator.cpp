#include "PreCompileHeader.h"
#include "PathOperator.h"
#include "../../../../RenderPath/AllRenderPath/PathBehavior.h"


//外部
#include "../../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

#include "../../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"


#include "../../../../../Resource/Model/ModelContextDiplomatIncludes.h"
#include "../../../../../Resource/Model/ModelContainer/ModelContainer.h"



RenderContext::StaticRenderGraph::PathOperator::PathOperator
(
	NexusFieldProof proof_,
	std::vector<PathBehavior*> const& allPathPtr_,
	PSO_PoolDispatcher& pso_PoolDispatcher_,
	std::vector<BufferTraits::BufferTag> const& traceRefBuffersTag_,
	std::array<std::vector<BufferUniqueID> , BuildOutput::PassSetUpper::kNumRefBufferType> const& refBuffersArr_,
	BufferUniqueID const targetFillInRefBufferID_

):
	allPathPtr(allPathPtr_),
	pso_PoolDispatcher(pso_PoolDispatcher_), 
	traceRefBuffersTag(traceRefBuffersTag_), 
	targetFillInRefBufferID(targetFillInRefBufferID_),
	refBuffersArr(refBuffersArr_)
{
	//参照バッファの総和と同じになるはずなので、確保しておく
	refBufferSrvIndices.resize(traceRefBuffersTag.size());
}

void RenderContext::StaticRenderGraph::PathOperator::FillInRefBufferSrvIndices
(
	UINT const frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//BufferDispatcherにアクセス
	auto bToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> bLicence;
	auto& bufferDispatcher = *bToolLender->Lend<BufferContext::BufferDispatcher>(bLicence);

	//参照バッファ群srv書き込み先のバッファ
	auto* dstBuffer = static_cast<UploadStructuredBuffer*>(bufferDispatcher.Dispatch(targetFillInRefBufferID));

	//参照バッファの格納順は記録しているので、そこからバッファを検索→srvIndex格納
	auto const numRefBuffers = traceRefBuffersTag.size();
	std::array<UINT, BuildOutput::PassSetUpper::kNumRefBufferType> refBufferCnts{};

	for (size_t i = 0;i< traceRefBuffersTag.size();++i)
	{
		//参照バッファの種類
		UINT refTagIndex = (UINT)traceRefBuffersTag[i];
		BufferUniqueID refID = refBuffersArr[refTagIndex][refBufferCnts[refTagIndex]++];
		GPUBufferBehavior* refBuffer = bufferDispatcher.Dispatch(refID);

		//なるべくdynamic_castつかいたくないんで
		//参照先バッファのsrvHeapIndexを記録
		if (traceRefBuffersTag[i] == BufferTraits::BufferTag::kColor)
		{
			refBufferSrvIndices[i] = static_cast<ColorBuffer*>(refBuffer)->OutProperSRVHeapIndex();
		}
		else
		{
			refBufferSrvIndices[i] = static_cast<DepthStencilBuffer*>(refBuffer)->OutProperSRVHeapIndex();
		}		
	}

	//参照バッファ格納先のバッファを検索
	auto* targetFillInRefBuffer = static_cast<UploadStructuredBuffer*>(bufferDispatcher.Dispatch(targetFillInRefBufferID));
	//参照先バッファのsrvIndex群をframeIndex = 書き込み先インデックス指定
	//で書き込む
	targetFillInRefBuffer->WriteRange<SRVHeapIndex>(frameIndex_, refBufferSrvIndices);


}

void RenderContext::StaticRenderGraph::PathOperator::Run
(
	UINT const frameIndex_,
	ModelContextDiplomat& modelContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	RuntimeWrapper& runtimeWrapper_
)
{
	FillInRefBufferSrvIndices(frameIndex_, bufferContextDiplomat_);

	//BufferDispatcherにアクセス
	auto bToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> bLicence;
	auto& bufferDispatcher = *bToolLender->Lend<BufferContext::BufferDispatcher>(bLicence);

	//modelContainer（仕分け済み）取得コマンドをもらう
	auto mCmdProvider = modelContextDiplomat_.Access<ModelContext::CommandProvider>();
	ModelContext::CommandProvider::LicenceType<ModelContextCmds::WatchSeparatedByRenderState> mLicence;
	auto& modelContainer = *mCmdProvider->Provide<ModelContextCmds::WatchSeparatedByRenderState>(mLicence)();

	
	for (auto* path : allPathPtr)
	{
		path->Run(modelContainer, modelFillMode, pso_PoolDispatcher, runtimeWrapper_, bufferDispatcher);
	}
}
