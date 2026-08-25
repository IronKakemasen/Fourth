#include "PreCompileHeader.h"
#include "Model.h"


Model::Model
(
	const std::vector<ModelDescription::Configurable>& modelDescConfigurables_,
	const std::vector<ModelDescription::Common>& modelDescCommons_,
	const std::vector<ModelDescription::Unique>& modelDescUniques_,
	std::string modelName_
) :modelDescConfigurables(modelDescConfigurables_), modelDescUniques(modelDescUniques_), modelDescCommons(modelDescCommons_), modelName(modelName_)
{
	
}

std::string const& Model::WatchName()const
{
	return modelName;
}