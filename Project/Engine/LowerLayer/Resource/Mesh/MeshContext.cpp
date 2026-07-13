#include "PreCompileHeader.h"
#include "MeshContext.h"
#include "CreateModelTools/ModelCreator.h"

namespace
{
	auto const fileName = "MeshContext.cpp";
}


MeshContext::MeshContext(const InstanceKey& key_)
{
	Logger::Entry("MeshContext: Constructor");

	modelCreator.reset(new ModelCreator(key_));
	Logger::Log("Instantiate: modelCreator", fileName);


	Logger::End("MeshContext: Constructor");

}

MeshContext::~MeshContext()
{

}
