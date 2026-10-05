#include "PreCompileHeader.h"
#include "ModelCreator.h"
#include "../ModelStructure/Model.h"
#include "ModelDescAssembler/ModelDescAssembler.h"
#include "../ModelContainer/ModelContainer.h"


namespace
{
	auto const fileName = "ModelCreator.cpp";
}

using namespace StructuredBufferModelData;

ModelContext::ModelCreator::ModelCreator
(
	NexusFieldProof proof_,
	std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
	ModelContext::ModelContainer& modelContainer_
) :modelDescAssembler(std::move(modelAssembler_)), modelContainer(modelContainer_)
{

}


std::vector<Model*> ModelContext::ModelCreator::Create
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
	UINT const numCreate_,
	std::string const& modelName_
)
{
	std::vector<Model*> modelPtrContainer;

	//モデルのディスクリプションの要素を組み立てる
	auto [perDrawIndices,materialsGPU,meshletSize] = modelDescAssembler->Assemble(modelFileName_, materials_);

	///一つのDescに詰める
	ModelDescription modelDesc
	(
		modelName_ + std::to_string(numCreate++),
		perDrawIndices,
		modelRenderStates_,
		meshletSize
	);

	for (UINT i = 0;i < numCreate_;++i)
	{
		///モデルクラスのインスタンス化
		std::unique_ptr<Model> model = std::make_unique<Model>(modelDesc, materialsGPU);

		modelPtrContainer.emplace_back(model.get());

		//実体はモデルコンテナが握る
		modelContainer.Add(ModelContainer::Local_AddLicence{}, std::move(model));
	}

	return modelPtrContainer;
}
