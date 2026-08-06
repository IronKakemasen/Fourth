#include "BufferContext.h"
#include "BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
//バッファ作成ツール
#include "BufferCreateTools/BufferCreator.h"
#include "BufferCreateTools/ResourceCreator/ResourceCreator.h"
//バッファをアップロード
#include "BufferCreateTools/BufferUploader/BufferUploader.h"
//各種ツールを外部へ貸し出します
#include "BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "BufferContextDiplomat/BufferContextDiplomat.h"
//ランタイム処理ツール
#include "BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "BufferRuntime/BufferInfoExtractor/BufferInfoExtractor.h"
#include "BufferContextDiplomat/BufferContextExecutionAgent/BufferContextExecutionAgent.h"
//ワールドコンスタントバッファの生成
#include "WorldConstantBuffers/ConstantBufferCreator/ConstantBufferCreator.h"
//から仮想GPUアドレスの保持
#include "WorldConstantBuffers/WorldConstantBuffers.h"
//バッファコレクターがバッファを仕分ける
#include "BufferPoolSet/BufferPoolSet.h"




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

	bufferDispatcher.reset(new BufferDispatcher(proof_, bufferPoolSet.get()));
	Logger::Log("Instantiate: bufferDispatcher", fileName);

	bufferCreator.reset
	(
		new BufferCreator
		(
			proof_, resourceCreator.get(), descriptorheapContextDiplomat_, bufferCollector.get(), bufferDispatcher.get()
		)
	);
	Logger::Log("Instantiate: BufferCreator", fileName);

	bufferUploader.reset(new BufferUploader(proof_, resourceCreator.get(),bufferDispatcher.get(), commandContextDiplomat_));
	Logger::Log("Instantiate: BufferUploader", fileName);

	worldConstantBuffers.reset(new WorldConstantBuffers(proof_));
	Logger::Log("Instantiate: worldConstantBuffers", fileName);

	constantBufferCreator.reset(new ConstantBufferCreator(proof_, worldConstantBuffers.get(),bufferCreator.get()));
	Logger::Log("Instantiate: constantBufferCreator", fileName);

	diplomat.reset
	(
		new BufferContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>
			(
				proof_,
				bufferCreator.get(),
				bufferUploader.get(),
				bufferDispatcher.get(),
				bufferCollector.get(),
				constantBufferCreator.get(),
				worldConstantBuffers.get()
			),
			std::make_unique<ExecutionAgent>(proof_, this, bufferUploader.get(),worldConstantBuffers.get())
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
void BufferContext::DeleteBufferUploader(const NexusFieldProof& proof_, AgentKey agentKey_)
{
	///中にある中間リソースをすべて削除
	bufferUploader.reset();
	Logger::Log("delete: bufferUploader", fileName);
}
