#pragma once
#include "../ModelContainer.h"
#include "../../ModelStructure/RenderState.h"


class KeyPackager;

class ModelContext::ModelContainer::ModelSeparator
{
public:

	ModelSeparator(NexusFieldProof proof_ ,AgentKey key_);
	~ModelSeparator();

	[[nodiscard]] std::vector<SepartatedContainer> SeparateAllModels(std::vector<std::unique_ptr<Model>>* modelContainer_);

private:

	//レンダーステートをキーに詰める
	std::vector<std::pair<RenderState, uint32_t>> PackToKey(Model const& model_);

	//レンダーステートキーをuint32_tに詰める
	std::unique_ptr<KeyPackager> keyPackager;
};

