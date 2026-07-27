#pragma once
#include "ModelDescription.h"
#include "../ModelContext.h"

class Model
{
public:

	Model
	(
		const std::vector<ModelDescription::Configurable>& modelDescConfigurables_,
		const std::vector<ModelDescription::Common>& modelDescCommons_,
		const std::vector<ModelDescription::Unique>& modelDescUniques_,
		std::string modelName_
	);

	std::string WatchName()const;

private:

	//ModelDescAssemblerに設定してもらう
	std::vector<ModelDescription::Common> modelDescCommons;
	std::vector<ModelDescription::Unique> modelDescUniques;
	//これだけは自分で決める
	std::string modelName;
	std::vector<ModelDescription::Configurable> modelDescConfigurables;

};

