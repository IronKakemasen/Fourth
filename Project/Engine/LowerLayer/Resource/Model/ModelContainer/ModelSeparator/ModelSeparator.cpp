#include "PreCompileHeader.h"
#include "ModelSeparator.h"
#include "../RenderStateKey/RenderStateKey.h"
#include "../../ModelStructure/Model.h"

//外部
#include "KeyPackager/KeyPackager.h"

using namespace RenderPassComponent;
using namespace RenderStateComponent;
using namespace ShaderPathComponent;


ModelContext::ModelContainer::ModelSeparator::ModelSeparator(NexusFieldProof proof_, AgentKey key_)
{
	keyPackager.reset
	(
		new KeyPackager
		(
			RenderStateKey::Count<RenderStateKey::Sequence::kPass>(),
			RenderStateKey::Count<RenderStateKey::Sequence::kBlendMode>(),
			RenderStateKey::Count<RenderStateKey::Sequence::kCullMode>(),
			RenderStateKey::Count<RenderStateKey::Sequence::kMeshType>(),
			RenderStateKey::Count<RenderStateKey::Sequence::kMaterialType>()
		)
	);
}

ModelContext::ModelContainer::ModelSeparator::~ModelSeparator()
{

}

[[nodiscard]] std::vector<std::unordered_map<uint32_t, std::vector<Model*>>>
ModelContext::ModelContainer::ModelSeparator::SeparateAllModels(std::vector<std::unique_ptr<Model>>* modelContainer_)
{
	std::vector<std::unordered_map<uint32_t, std::vector<Model*>>> data;
	data.resize(UINT(RenderPassComponent::Pass::kCount));

	for (auto itr = modelContainer_->begin();itr != modelContainer_->end();++itr)
	{
		auto packedKeys = PackToKey(*(*itr));
		for (auto const& key : packedKeys)
		{
			data[(UINT)key.first][key.second].emplace_back((*itr).get());
		}
	}

	return data;
}

std::vector<std::pair<RenderPassComponent::Pass, uint32_t>> ModelContext::ModelContainer::ModelSeparator::PackToKey(Model const& model_)
{
	std::vector<std::pair<RenderPassComponent::Pass, uint32_t>> keys;

	for (auto const& renderState : model_.WatchRenderStates())
	{
		for (auto const& blendMode : renderState.blendModes)
		{
			uint32_t packedKey = keyPackager->Pack
			(
				renderState.pass,
				blendMode,
				renderState.cullMode,
				renderState.meshType,
				renderState.materialType
			);

			keys.emplace_back(std::make_pair(renderState.pass , packedKey));
		}
	}

	return keys;
}