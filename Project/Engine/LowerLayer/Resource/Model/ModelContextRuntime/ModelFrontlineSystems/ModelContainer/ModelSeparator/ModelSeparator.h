#pragma once
#include "../ModelContainer.h"


class KeyPackager;

class ModelContext::FrontlineSystems::ModelContainer::ModelSeparator
{
public:

	ModelSeparator();
	~ModelSeparator();

	[[nodiscard]] std::vector<ModelContext::FrontlineSystems::ModelContainer::SeparatedByRenderState> 
		SeparateAllModels(std::vector<std::unique_ptr<Model>>& modelContainer_);

private:

	//レンダーステートをキーに詰める
	std::vector<std::pair<RenderStateKey, uint64_t>> PackToKey(Model const& model_);

	//レンダーステートキーをuint32_tに詰める
	std::unique_ptr<KeyPackager> keyPackager;
};

