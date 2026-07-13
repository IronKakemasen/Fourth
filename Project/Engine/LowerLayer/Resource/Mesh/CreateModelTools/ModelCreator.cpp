#include "PreCompileHeader.h"
#include "ModelCreator.h"

//ツール
#include "ModelDataLoader/ModelDataLoader.h"

namespace
{
	auto const fileName = "ModelCreator.cpp";
}


MeshContext::ModelCreator::ModelCreator(MeshContext::InstanceKey key_)
{
	Logger::Entry("ModelCreator: Constructor");



	modelDataLoader.reset(new ModelDataLoader(key_));
	Logger::Log("Instantiate: ModelDataLoader", fileName);



	Logger::End("ModelCreator: Constructor");
}

MeshContext::ModelCreator::~ModelCreator()
{

}
