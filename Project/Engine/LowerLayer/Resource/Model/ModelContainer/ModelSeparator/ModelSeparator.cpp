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

[[nodiscard]] std::vector<ModelContext::ModelContainer::SepartatedContainer>
ModelContext::ModelContainer::ModelSeparator::SeparateAllModels(std::vector<std::unique_ptr<Model>>* modelContainer_)
{
	std::vector<SepartatedContainer> dstSeparateContainer;

	dstSeparateContainer.resize((UINT)Pass::kCount);

	for (auto itr = modelContainer_->begin();itr != modelContainer_->end();++itr)
	{
		//renderStateとそのパックされたキーがセット
		auto packedKeys = PackToKey(*(*itr));

		for (auto const& key : packedKeys)
		{
			auto const pass = (UINT)key.first.Get<RenderStateKey::Sequence::kPass>();
			dstSeparateContainer[pass][key.second].first = key.first;
			dstSeparateContainer[pass][key.second].second.emplace_back((*itr).get());
		}
	}

	return dstSeparateContainer;
}

std::vector<std::pair<RenderStateKey, uint32_t>> ModelContext::ModelContainer::ModelSeparator::PackToKey(Model const& model_)
{
	std::vector<std::pair<RenderStateKey, uint32_t>> keys;

	for (auto const& renderState : model_.WatchRenderStates())
	{
		for (auto const& blendMode : renderState.blendModes)
		{
			for (auto const& materialType : renderState.materialTypes)
			{
				uint32_t packedKey = keyPackager->Pack
				(
					renderState.pass,
					blendMode,
					renderState.cullMode,
					renderState.meshType,
					materialType
				);

				RenderStateKey renderStateKey
				(
					renderState.pass,
					blendMode,
					renderState.cullMode,
					renderState.meshType,
					materialType
				);


				keys.emplace_back(std::make_pair(renderStateKey, packedKey));
			}
		}
	}

	return keys;
}