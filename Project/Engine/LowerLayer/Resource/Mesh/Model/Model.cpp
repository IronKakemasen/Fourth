#include "PreCompileHeader.h"
#include "Model.h"


Model::Model(std::string fileName_, const std::vector<ModelDescription::Configurable>& modelDataConfigurables_)
	:fileName(fileName_), modelDataConfigurables(modelDataConfigurables_)
{
	
}
