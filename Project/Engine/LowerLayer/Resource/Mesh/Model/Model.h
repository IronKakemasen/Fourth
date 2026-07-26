#pragma once
#include "ModelDescription.h"


class Model
{
public:

	Model(std::string fileName_, const std::vector<ModelDescription::Configurable>& modelDataConfigurable_);


private:
	std::string fileName;

	std::vector<std::shared_ptr<ModelDescription::Common>> modelDataCommon;
	std::vector<ModelDescription::Unique> modelDataUnique;
	std::vector<ModelDescription::Configurable> modelDataConfigurable;

};

