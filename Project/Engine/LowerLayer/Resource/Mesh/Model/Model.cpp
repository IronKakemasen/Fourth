#include "PreCompileHeader.h"
#include "Model.h"


Model::Model
(
	const std::vector<ModelDescription::Configurable>& modelDataConfigurables_,
	const std::vector<ModelDescription::Unique>& modelDataUniques_,
	const std::vector<ModelDescription::Common>& modelDataCommons_,
	std::string modelName_
) :modelDataConfigurables(modelDataConfigurables_), modelDataUniques(modelDataUniques_), modelDataCommons(modelDataCommons_), modelName(modelName_)
{
	
}
