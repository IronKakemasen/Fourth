#include "PreCompileHeader.h"
#include "ModelCreator.h"

#include "ModelDescAssembler/ModelDescAssembler.h"



MeshContext::ModelCreator::ModelCreator(NexusFieldProof proof_, std::unique_ptr<MeshContext::ModelDescAssembler>&& modelAssembler_)
	:ModelDescAssembler(std::move(modelAssembler_))
{

}


Model* MeshContext::ModelCreator::Create
(
	std::string modelFileName_,
	const std::vector<ModelDescription::Configurable>& modelDataConfigurables_,
	std::string modelName_
)
{
	


	return nullptr;
}
