#include "PreCompileHeader.h"
#include "Model.h"

namespace
{
	auto const fileName = "Model.cpp";
}

using namespace ProjectConfig::Render;

Model::Model
(
	const ModelDescription& modelDesc_,
	std::vector<Materials> materialsContainer_
) :modelDesc(modelDesc_)
{
	//変更可能描画コンポーネントの初期設定は添え字0番に
	changeableParams.blendMode = modelDesc_.WatchRenderStates()[0].blendModes[0];
	changeableParams.materialType = modelDesc_.WatchRenderStates()[0].materialTypes[0];

	///gennkouuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
	changeableParams.materialsContainer = std::move(materialsContainer_);


	//サブメッシュ分のトランスフォームを確保
	auto const numMeshes = modelDesc_.WatchModelConstants().size();
	changeableParams.transforms.resize(numMeshes);
	//サブメッシュのペアレント化
	auto& mainTrans = changeableParams.transforms[0];
	for (size_t i = 1;i < numMeshes;++i)
	{
		mainTrans.BeParent(&changeableParams.transforms[i]);
	}
}

void Model::ChangeBlendMode(RenderStateComponent::BlendMode dst_)
{
	bool hasConfigured{};
	//そもそもこのコンポーネントパターンを構築しているか
	for (auto const& renderState : WatchRenderStates())
	{
		for (auto const blendMode : renderState.blendModes)
		{
			if (dst_== blendMode)
			{
				hasConfigured = true;
				break;
			}
		}
	}

	ErrorMessageOutput::Assert::DetectError
	(
		hasConfigured,
		WatchName() + "に設定していないblendModeへの変更を検知",
		fileName
	);

	changeableParams.blendMode = dst_;

}

void Model::ChangeMaterialType(Material::Type dst_)
{
	bool hasConfigured{};
	//そもそもこのコンポーネントパターンを構築しているか
	for (auto const& renderState : WatchRenderStates())
	{
		for (auto const materialType : renderState.materialTypes)
		{
			if (dst_ == materialType)
			{
				hasConfigured = true;
				break;
			}
		}
	}

	ErrorMessageOutput::Assert::DetectError
	(
		hasConfigured,
		WatchName() + "に設定していないMaterialTypeへの変更を検知",
		fileName
	);

	changeableParams.materialType = dst_;
}

