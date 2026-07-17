#include "PreCompileHeader.h"
#include "MeshContext.h"
#include "CreateModelTools/ModelDataCreator/ModelDataCreator.h"

namespace
{
	auto const fileName = "MeshContext.cpp";
}


MeshContext::MeshContext(const InstanceKey& key_)
{
	Logger::Entry("MeshContext: Constructor");

	modelDataCreator.reset(new ModelDataCreator(key_));
	Logger::Log("Instantiate: ModelDataCreator", fileName);


	Logger::End("MeshContext: Constructor");

}

MeshContext::~MeshContext()
{

}
