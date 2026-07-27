#pragma once
#include "ModelDescription.h"
#include "../MeshContext.h"

class Model
{
public:

	Model
	(
		const std::vector<ModelDescription::Configurable>& modelDataConfigurables_,
		const std::vector<ModelDescription::Unique>& modelDataUniques_,
		const std::vector<ModelDescription::Common>& modelDataCommons_,
		std::string modelName_
	);


private:

	friend class MeshContext::ModelDescAssembler;

	//ModelDescAssemblerに設定してもらう
	std::vector<ModelDescription::Common> modelDataCommons;
	std::vector<ModelDescription::Unique> modelDataUniques;
	//これだけは自分で決める
	std::string modelName;
	std::vector<ModelDescription::Configurable> modelDataConfigurables;

};

