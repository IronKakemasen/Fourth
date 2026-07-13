#pragma once
#include "../../MeshContext.h"

struct ResourceMesh;
struct ResourceMaterial;


class MeshContext::ModelDataLoader
{
	class ModelDataCache;

	std::unique_ptr<ModelDataCache> modelDataCache;

public:

	ModelDataLoader(MeshContext::InstanceKey key_);
	~ModelDataLoader();

	void Load
	(
		std::string fileName_,
		std::vector<ResourceMesh>& meshes_,
		std::vector<ResourceMaterial>& materials_
	);


};

