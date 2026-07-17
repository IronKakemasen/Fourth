#pragma once
#include "../MeshContext.h"

struct ModelDescription;

class Model
{
	struct CreateKey;

	Model(std::unique_ptr<ModelDescription>&& desc_);


private:
	std::unique_ptr<ModelDescription> desc;

};

struct Model::CreateKey
{
private:

	friend class MeshContext::ModelDataCreator;
	explicit CreateKey() = default;
};


