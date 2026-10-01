#include "PreCompileHeader.h"
#include "PathOperator.h"
#include "../../../../RenderPath/AllRenderPath/PathBehavior.h"


//外部
#include "../../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

#include "../../../../../Buffer/BufferContextDiplomats.h"
#include "../../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"


#include "../../../../../Resource/Model/ModelContextDiplomatIncludes.h"
#include "../../../../../Resource/Model/ModelContainer/ModelContainer.h"



RenderContext::StaticRenderGraph::PathOperator::PathOperator
(
	NexusFieldProof proof_,
	std::vector<PathBehavior*> const& allPathPtr_,
	PSO_PoolDispatcher& pso_PoolDispatcher_,
	std::vector<BufferUniqueID> const& refBuffers_,
	BufferUniqueID const targetFillInRefBufferID_

):allPathPtr(allPathPtr_), pso_PoolDispatcher(pso_PoolDispatcher_), refBuffers(refBuffers_), targetFillInRefBufferID(targetFillInRefBufferID_)
{

}

void RenderContext::StaticRenderGraph::PathOperator::FillInRefBufferSrvIndices(BufferContextDiplomat& bufferContextDiplomat_)
{
	//BufferDispatcherにアクセス
	auto bToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> bLicence;
	auto& bufferDispatcher = *bToolLender->Lend<BufferContext::BufferDispatcher>(bLicence);

	//参照バッファsrv格納先のバッファ
	auto* dstBuffer = bufferDispatcher.Dispatch(targetFillInRefBufferID);


}

void RenderContext::StaticRenderGraph::PathOperator::Run
(
	UINT const frameIndex_,
	ModelContextDiplomat& modelContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_,
	RuntimeWrapper& runtimeWrapper_
)
{
	//BufferDispatcherにアクセス
	auto bToolLender = bufferContextDiplomat_.Access<BufferContext::ToolLender>();
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> bLicence;
	auto& bufferDispatcher = *bToolLender->Lend<BufferContext::BufferDispatcher>(bLicence);

	//modelContainer（仕分け済み）取得コマンドをもらう
	auto mCmdProvider = modelContextDiplomat_.Access<ModelContext::CommandProvider>();
	ModelContext::CommandProvider::LicenceType<ModelContextCmds::WatchSeparatedModelContainer> mLicence;
	auto& modelContainer = *mCmdProvider->Provide<ModelContextCmds::WatchSeparatedModelContainer>(mLicence)();

	for (auto* path : allPathPtr)
	{
		path->Run(modelContainer, modelFillMode, pso_PoolDispatcher, runtimeWrapper_, bufferDispatcher);
	}
}
