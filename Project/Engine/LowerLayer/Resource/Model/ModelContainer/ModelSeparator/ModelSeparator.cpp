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

[[nodiscard]] ModelContext::ModelContainer::ModelSeparator::Output
ModelContext::ModelContainer::ModelSeparator::SeparateAllModels(std::vector<std::unique_ptr<Model>>& modelContainer_)
{
	std::vector<SeparatedByRenderState> separatedByRenderState;
	std::array < std::vector<Model*>, (UINT)Model::Type::kCount> separatedByModelType;

	separatedByRenderState.resize((UINT)Pass::kCount);

	for (auto itr = modelContainer_.begin();itr != modelContainer_.end();++itr)
	{
		//renderStateとそのパックされたキーがセット
		auto packedKeys = PackToKey(*(*itr));

		//RenderState別に仕分けていく
		for (auto const& key : packedKeys)
		{
			auto const pass = (UINT)key.first.Get<RenderStateKey::Sequence::kPass>();
			separatedByRenderState[pass][key.second].first = key.first;
			separatedByRenderState[pass][key.second].second.emplace_back((*itr).get());
		}

		//ランタイムデータバッチング用にモデルタイプ別に仕分けていく
		separatedByModelType[(UINT)(*itr)->WatchModelType()].emplace_back((*itr).get());
	}

	return std::make_pair(separatedByRenderState, separatedByModelType);
}

std::vector<std::pair<RenderStateKey, uint64_t>> ModelContext::ModelContainer::ModelSeparator::PackToKey(Model const& model_)
{
	std::vector<std::pair<RenderStateKey, uint64_t>> keys;

	for (auto const& renderState : model_.WatchRenderStates())
	{
		for (auto const& blendMode : renderState.blendModes)
		{
			for (auto const& materialType : renderState.materialTypes)
			{
				uint64_t packedKey = keyPackager->Pack
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