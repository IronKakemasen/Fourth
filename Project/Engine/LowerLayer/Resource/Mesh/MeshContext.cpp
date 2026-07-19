#include "PreCompileHeader.h"
#include "MeshContext.h"
#include "CreateModelTools/ModelDataCreator/ModelDataCreator.h"
#include "CreateModelTools/ModelSlotAllocator/ModelSlotAllocator.h"


namespace
{
	auto const fileName = "MeshContext.cpp";
}


MeshContext::MeshContext(const InstanceKey& key_, BufferContext* bufferContext_)
{
	Logger::Entry("MeshContext: Constructor");

	modelSlotAllocator.reset(new ModelSlotAllocator(key_));
	Logger::Log("Instantiate: modelSlotAllocator", fileName);

	modelDataCreator.reset(new ModelDataCreator(key_, modelSlotAllocator.get(), bufferContext_));
	Logger::Log("Instantiate: ModelDataCreator", fileName);


	Logger::End("MeshContext: Constructor");

}

MeshContext::~MeshContext()
{

}
