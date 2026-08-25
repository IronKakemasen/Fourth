#pragma once
#include "ModelDescription.h"

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

	 std::string const& WatchName()const;

	const std::vector<ModelDescription::Configurable>& WatchConfigurableData()const
	{
		return modelDescConfigurables;
	}

private:

	//ModelDescAssemblerに設定してもらう
	std::vector<ModelDescription::Common> modelDescCommons;
	std::vector<ModelDescription::Unique> modelDescUniques;
	//これ以下は自分で決める
	std::string modelName;
	std::vector<ModelDescription::Configurable> modelDescConfigurables;

};

