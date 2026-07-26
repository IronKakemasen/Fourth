#pragma once
#include "ModelDescription.h"
#include "../MeshContext.h"

class Model
{
public:

	Model(std::string fileName_, const std::vector<ModelDescription::Configurable>& modelDataConfigurables_);


private:

	friend class MeshContext::ModelAssembler;

	std::string fileName;
	std::vector<ModelDescription::Common> modelDataCommons;
	std::vector<ModelDescription::Unique> modelDataUniques;
	std::vector<ModelDescription::Configurable> modelDataConfigurables;

};

