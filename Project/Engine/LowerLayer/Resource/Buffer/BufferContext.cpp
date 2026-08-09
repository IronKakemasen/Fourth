#include "BufferContext.h"
#include "BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
//バッファ作成ツール
#include "BufferCreateTools/BufferCreator.h"
#include "BufferCreateTools/ResourceCreator/ResourceCreator.h"
//バッファをアップロード
#include "BufferCreateTools/BufferUploader/BufferUploader.h"
//各種ツールを外部へ貸し出します
#include "BufferContextDiplomat/BufferContextDiplomat.h"
#include "BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "BufferContextDiplomat/BufferContextCmdProvider/BufferContextCmdProvider.h"
#include "BufferContextDiplomat/BufferContextExecutionAgent/BufferContextExecutionAgent.h"
//ランタイム処理ツール
#include "BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "BufferRuntime/BufferInfoExtractor/BufferInfoExtractor.h"
//ワールドコンスタントバッファの生成
#include "GlobalConstantBuffers/GlobalConstantBufferCreator/GlobalConstantBufferCreator.h"
//から仮想GPUアドレスの保持
#include "GlobalConstantBuffers/GlobalConstantBuffers.h"
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

	globalConstantBuffers.reset(new GlobalConstantBuffers(proof_));
	Logger::Log("Instantiate: GlobalConstantBuffers", fileName);

	globalConstantBufferCreator.reset(new GlobalConstantBufferCreator(proof_, globalConstantBuffers.get(),bufferCreator.get()));
	Logger::Log("Instantiate: GlobalConstantBufferCreator", fileName);

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
				globalConstantBuffers.get()
			),
			std::make_unique<ExecutionAgent>(proof_, this, bufferUploader.get(),globalConstantBuffers.get()),
			std::make_unique<CmdProvider>(proof_, globalConstantBufferCreator.get())
		)
	);

	Logger::Log("Instantiate: ToolLender", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);
	Logger::Log("Instantiate: BufferContextDiplomat", fileName);
	Logger::Log("Instantiate: CmdProvider", fileName);




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
