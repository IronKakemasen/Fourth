#include "PreCompileHeader.h"
#include "PathOperator.h"
#include "../../../../RenderPath/AllRenderPath/PathBehavior.h"


//外部
#include "../../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

#include "../../../../../Buffer/BufferContextDiplomats.h"

#include "../../../../../Resource/Model/ModelContextDiplomatIncludes.h"
#include "../../../../../Resource/Model/ModelContainer/ModelContainer.h"



RenderContext::StaticRenderGraph::PathOperator::PathOperator
(
	NexusFieldProof proof_,
	std::vector<PathBehavior*> const& allPathPtr_,
	PSO_PoolDispatcher& pso_PoolDispatcher_

):allPathPtr(allPathPtr_), pso_PoolDispatcher(pso_PoolDispatcher_)
{

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
