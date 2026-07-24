#include "BufferContext.h"
#include "BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
//バッファ作成ツール
#include "BufferCreateTools/BufferCreator.h"
#include "BufferCreateTools/ResourceCreator/ResourceCreator.h"
//バッファをアップロード
#include "BufferCreateTools/BufferUploader/BufferUploader.h"
//各種ツールを下位部へ貸し出します
#include "BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "BufferContextDiplomat/BufferContextDiplomat.h"
//ランタイム処理ツール
#include "BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "BufferRuntime/BufferInfoExtractor/BufferInfoExtractor.h"
#include "BufferContextDiplomat/BufferContextExecutionAgent/BufferContextExecutionAgent.h"

#include "ClosedHashMap/ClosedHashMap.h" 


namespace
{
	std::string fileName = "BufferContext.cpp";
}

BufferContext::BufferContext
(
	NexusFieldProof proof_,
	DeviceContextDiplomat* deviceContextDiplomat_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
	CommandContextDiplomat* commandContextDiplomat_
)
{
	Logger::Entry("BufferContext: Constructor");

	bufferPoolSet.reset(new BufferPoolSet());
	Logger::Log("Create: bufferPoolSet", fileName);

	bufferCollector.reset(new BufferContext::BufferCollector(proof_, bufferPoolSet.get()));
	Logger::Log("Instantiate: bufferCollector", "BufferCreator.cpp");

	resourceCreator.reset(new BufferContext::ResourceCreator(proof_, deviceContextDiplomat_));
	Logger::Log("Instantiate: ResourceCreator", fileName);

	bufferCreator.reset(new BufferCreator(proof_, resourceCreator.get(), descriptorheapContextDiplomat_, bufferCollector.get()));
	Logger::Log("Instantiate: BufferCreator", fileName);

	bufferDispatcher.reset(new BufferDispatcher(proof_, bufferPoolSet.get()));
	Logger::Log("Instantiate: bufferDispatcher", fileName);

	bufferUploader.reset(new BufferUploader(proof_, resourceCreator.get(),bufferDispatcher.get(), commandContextDiplomat_));
	Logger::Log("Instantiate: BufferUploader", fileName);

	diplomat.reset
	(
		new BufferContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, bufferCreator.get(), bufferUploader.get(), bufferDispatcher.get(), bufferCollector.get()),
			std::make_unique<ExecutionAgent>(proof_, this, bufferUploader.get())
		)
	);

	Logger::Log("Instantiate: ToolLender", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);
	Logger::Log("Instantiate: BufferContextDiplomat", fileName);

	Logger::End("BufferContext: Constructor");

}

BufferContext::~BufferContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::unique_ptr<GPUBufferBehavior>>* BufferContext::BufferPoolSet::ContainerTable(BufferContext::RegisterType type_)
{
	static std::vector<std::unique_ptr<GPUBufferBehavior>>* table[(int)BufferContext::RegisterType::kCount]
	{
		&renderTargetBufferPool,
		&frameBufferPool,
		&computeBufferPool,
		&readOnlyBufferPool
	};

	return table[(int)type_];
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BufferContext::BufferPoolSet::BufferPoolSet()
{
	bufferLocationClosedHashedMap.reset(new ClosedHashMap<std::pair<RegisterType, uint32_t>>(kHashedMapSize));
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::DeleteBufferUploader(const NexusFieldProof& proof_, AgentKey agentKey_)
{
	///中にある中間リソースをすべて削除
	bufferUploader.reset();
	Logger::Log("delete: bufferUploader", fileName);
}
