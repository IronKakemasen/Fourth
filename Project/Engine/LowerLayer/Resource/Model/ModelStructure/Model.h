#pragma once
#include "ModelDescription/ModelDescription.h"

class Model
{
public:

	Model(const ModelDescription& modelDesc_);

	 std::string const WatchName()const;

	auto const& WatchRenderStates()const
	{
		return modelDesc.WatchRenderStates();
	}

private:

	ModelDescription modelDesc;

};

