#pragma once
#include "ModelDescription/ModelDescription.h"

class Model
{
public:

	Model(const ModelDescription& modelDesc_);

	 std::string const& WatchName()const;

	const ModelDescription* WatchModelDesc()const
	{
		return &modelDesc;
	}

private:

	ModelDescription modelDesc;

};

