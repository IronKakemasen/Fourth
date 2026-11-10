#include "PreCompileHeader.h"
#include "MaterialContext.h"
#include "MaterialBufferCreator/MaterialBufferCreator.h"
#include "MaterialIndexDispatcher/MaterialIndexDispatcher.h"
#include "MaterialAttacher/MaterialAttacher.h"

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

	//マテリアル関連のバッファを作成
	MaterialBufferCreator materialBufferCreator(proof_, *materialIndexDispatcher, bufferContextDiplomat_);

	materialAttacher = std::make_unique<MaterialAttacher>(proof_, *materialIndexDispatcher, bufferContextDiplomat_);
	Logger::Log("Instantiate: MaterialAttacher", fileName);



	Logger::End("MaterialContext: Constructor");

}	

MaterialContext::~MaterialContext()
{

}