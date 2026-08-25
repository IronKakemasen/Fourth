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
	const std::vector<ModelDescription::Configurable>& modelDataConfigurables_,
	std::string modelName_
)
{
	//modelDataConfigurables_の中身がちゃんと埋まってるかチェック
	for (auto const& data : modelDataConfigurables_)
	{
		ErrorMessageOutput::Assert::DetectError
		(
			(data.blendModes.size() > 0) && (data.passes != RenderStateComponent::RenderPass::kNone),
			modelName_ + "のModelDescription::Configurableのデータがちゃんと埋まってない",
			fileName
		);
	}

	//commonとuniqueのディスクリプション
	auto commons_uniques = modelDescAssembler->Assemble(modelFileName_);

	std::unique_ptr<Model> model = std::make_unique<Model>
	(
		modelDataConfigurables_,
		commons_uniques.first,
		commons_uniques.second,
		modelName_ + std::to_string(numCreate++)
	);

	//比がおなじかチェックしておく
	ErrorMessageOutput::Assert::DetectError
	(
		((modelDataConfigurables_.size() == commons_uniques.first.size()) &&
		(modelDataConfigurables_.size() == commons_uniques.second.size())),
		"なんかサイズがちげーど？",
		fileName
	);

	Model* modelPtr = model.get();

	//実体はモデルコンテナが握る
	modelContainer->Add(ModelContainer::Local_AddLicence{}, std::move(model));

	return modelPtr;
}
