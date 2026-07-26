#include "PreCompileHeader.h"
#include "Model.h"


Model::Model(std::string fileName_, const std::vector<ModelDescription::Configurable>& modelDataConfigurable_)
	:fileName(fileName_), modelDataConfigurable(modelDataConfigurable_)
{
	
}
