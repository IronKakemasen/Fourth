#pragma once
#include "../ModelContext.h"


//外部
#include "../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../ModelStructure/Model.h"

struct RenderState;

class ModelContext::ModelCreator
{
public:

	ModelCreator
	(
		NexusFieldProof proof_, 
		std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
		ModelContext::ModelContainer& modelContainer_
	);

	std::vector<Model*> Create
	(
		std::string const& modelFileName_,
		Model::Type type_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_ = "nameLess"
	);


private:

	//生成数。ネーミング用
	UINT numCreate{};
	//モデルディスク組み立て役
	std::unique_ptr<ModelContext::ModelDescAssembler> modelDescAssembler;
	
	//生成したユニークはこいつが管理する
	ModelContext::ModelContainer& modelContainer;
	
};

