#include "PreCompileHeader.h"
#include "ModelCreator.h"
#include "../ModelStructure/Model.h"
#include "ModelDescAssembler/ModelDescAssembler.h"
#include "../ModelContainer/ModelContainer.h"

namespace
{
	auto const fileName = "ModelCreator.cpp";
}


ModelContext::ModelCreator::ModelCreator
(
	NexusFieldProof proof_,
	std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
	ModelContext::ModelContainer* modelContainer_
) :modelDescAssembler(std::move(modelAssembler_)), modelContainer(modelContainer_)
{

}


Model* ModelContext::ModelCreator::Create
(
	std::string modelFileName_,
	const std::vector<ModelDescription::RenderState>& modelRenderStates_,
	std::string modelName_
)
{
	//commonとuniqueのディスクリプション
	auto commons_uniques = modelDescAssembler->Assemble(modelFileName_);


	///一つのDescに詰める
	ModelDescription modelDesc
	(
		commons_uniques.first,
		commons_uniques.second,
		modelName_ + std::to_string(numCreate++),
		modelRenderStates_
	);
	///モデルクラスのインスタンス化
	std::unique_ptr<Model> model = std::make_unique<Model>(modelDesc);

	Model* modelPtr = model.get();

	//実体はモデルコンテナが握る
	modelContainer->Add(ModelContainer::Local_AddLicence{}, std::move(model));

	return modelPtr;
}
