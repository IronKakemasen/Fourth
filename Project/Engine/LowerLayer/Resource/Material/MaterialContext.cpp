#include "PreCompileHeader.h"
#include "MaterialContext.h"
#include "MaterialBufferCreator/MaterialBufferCreator.h"
#include "MaterialIndexDispatcher/MaterialIndexDispatcher.h"
#include "MaterialAttacher/MaterialAttacher.h"
#include "MaterialContextDiplomat/MaterialContextDiplomat.h"
#include "MaterialContextDiplomat/MaterialExecutionAgent/MaterialExecutionAgent.h"
#include "MaterialContextDiplomat/MaterialToolLender/MaterialToolLender.h"


namespace
{
	auto fileName = "MaterialContext.cpp";
}

MaterialContext::MaterialContext
(
	NexusFieldProof proof_,
	BufferContextDiplomat& bufferContextDiplomat_
) 
{
	Logger::Entry("MaterialContext: Constructor");


	materialIndexDispatcher = std::make_unique<MaterialIndexDispatcher>(proof_);
	Logger::Log("Instantiate: MaterialIndexDispatcher", fileName);

	materialDataBatcher = std::make_unique<MaterialDataBatcher>(proof_);
	Logger::Log("Instantiate: MaterialDataBatcher", fileName);

	//マテリアル関連のバッファを作成
	MaterialBufferCreator materialBufferCreator(proof_, *materialDataBatcher, bufferContextDiplomat_);

	materialAttacher = std::make_unique<MaterialAttacher>(proof_, *materialIndexDispatcher, *materialDataBatcher);
	Logger::Log("Instantiate: MaterialAttacher", fileName);

	materialContextDiplomat = std::make_unique<MaterialContextDiplomat>
	(
		proof_,
		std::make_unique<ExecutionAgent>(proof_, *materialDataBatcher),
		std::make_unique<ToolLender>(proof_, materialAttacher.get())
	);
	Logger::Log("Instantiate: MaterialContextDiplomat", fileName);
	Logger::Log("Instantiate: ExecutionAgent", fileName);
	Logger::Log("Instantiate: ToolLender", fileName);


	Logger::End("MaterialContext: Constructor");

}	

MaterialContext::~MaterialContext()
{

}