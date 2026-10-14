#pragma once
#include "../ModelContainer.h"


class KeyPackager;

class ModelContext::ModelFrontlineSystems::ModelContainer::ModelSeparator
{
	using Output = std::pair<std::vector<SeparatedByRenderState>, std::array < std::vector<Model*>, (UINT)Model::Type::kCount > >;

public:

	ModelSeparator();
	~ModelSeparator();

	[[nodiscard]] Output SeparateAllModels(std::vector<std::unique_ptr<Model>>& modelContainer_);

private:

	//レンダーステートをキーに詰める
	std::vector<std::pair<RenderStateKey, uint64_t>> PackToKey(Model const& model_);

	//レンダーステートキーをuint32_tに詰める
	std::unique_ptr<KeyPackager> keyPackager;
};

