#pragma once
#include "../ModelContext.h"
#include "../ModelStructure/ModelDescription/ModelDescription.h"

class Model;

class ModelContext::ModelCreator
{
public:

	ModelCreator
	(
		NexusFieldProof proof_, 
		std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
		ModelContext::ModelContainer& modelContainer_
	);

	Model* Create
	(
		std::string const modelFileName_,
		std::vector<ModelDescription::RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		std::string const modelName_ = "nameLess"
	);

private:

	//生成数。ネーミング用
	UINT numCreate{};
	//モデルディスク組み立て役
	std::unique_ptr<ModelContext::ModelDescAssembler> modelDescAssembler;
	//生成したユニークはこいつが管理する
	ModelContext::ModelContainer& modelContainer;
	
};

