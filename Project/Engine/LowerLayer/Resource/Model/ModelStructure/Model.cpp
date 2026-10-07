#include "PreCompileHeader.h"
#include "Model.h"

namespace
{
	auto const fileName = "Model.cpp";
}

Model::Model
(
	Type type_,
	const ModelDescription& modelDesc_,
	std::vector<StructuredBufferModelData::MaterialGPU> const& materials_
) :modelDesc(modelDesc_), type(type_)
{
	//変更可能描画コンポーネントの初期設定は添え字0番に
	changeableParams.blendMode = modelDesc_.WatchRenderStates()[0].blendModes[0];
	changeableParams.materialType = modelDesc_.WatchRenderStates()[0].materialTypes[0];

	changeableParams.materials = materials_;
	changeableParams.areMaterialsDirty.resize(materials_.size(),true);

	//サブメッシュ分のトランスフォームを確保
	auto const numMeshes = modelDesc_.WatchPerDrawIndices().size();
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

void Model::ChangeMaterialType(ShaderPathComponent::MaterialType dst_)
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

void Model::ChangeRoughness(size_t index_, float dst_)
{
	static auto const errorMsg = WatchName() + "のラフネスアクセス違反";
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.materials.size(),
		errorMsg,
		fileName
	);

	changeableParams.areMaterialsDirty[index_] = true;
	changeableParams.materials[index_].roughness = dst_;
}

void Model::ChangeMetalic(size_t index_, float dst_)
{
	static auto const errorMsg = WatchName() + "のメタリックアクセス違反";
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.materials.size(),
		errorMsg,
		fileName
	);

	changeableParams.areMaterialsDirty[index_] = true;
	changeableParams.materials[index_].metallic = dst_;

}

void Model::ChangeColor(size_t index_, Vector4<float> const& dst_)
{
	static auto const errorMsg = WatchName() + "のカラーインデックスアクセス違反";
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.materials.size(),
		errorMsg,
		fileName
	);

	changeableParams.areMaterialsDirty[index_] = true;
	changeableParams.materials[index_].baseColor = dst_;
}

Transform& Model::RefTransform(size_t index_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.transforms.size(),
		WatchName() + "には" + std::to_string(index_) + "番目のトランスフォームはない",
		fileName
	);

	return changeableParams.transforms[index_];
}

std::span<Transform> Model::RefTransforms()
{
	return changeableParams.transforms;
}

template<>
void Model::ChangeTexture<TextureComponent::TextureType::kAlbedo>(size_t index_, SRVHeapIndex dst_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.materials.size(),
		WatchName() + "のアルベドテクスチャアクセス違反",
		fileName
	);

	changeableParams.areMaterialsDirty[index_] = true;
	changeableParams.materials[index_].albedoTexture = dst_;
}
template<>
void Model::ChangeTexture<TextureComponent::TextureType::kNormal>(size_t index_, SRVHeapIndex dst_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.materials.size(),
		WatchName() + "の法線テクスチャアクセス違反",
		fileName
	);

	changeableParams.areMaterialsDirty[index_] = true;
	changeableParams.materials[index_].normalTexture = dst_;
}
template<>
void Model::ChangeTexture<TextureComponent::TextureType::kEmissive>(size_t index_, SRVHeapIndex dst_)
{
	ErrorMessageOutput::Assert::DetectError
	(
		index_ < changeableParams.materials.size(),
		WatchName() + "のエミッシブテクスチャアクセス違反",
		fileName
	);

	changeableParams.areMaterialsDirty[index_] = true;
	changeableParams.materials[index_].emissiveTexture = dst_;
}


template
void Model::ChangeTexture<TextureComponent::TextureType::kAlbedo>(size_t index_, SRVHeapIndex dst_);
template
void Model::ChangeTexture<TextureComponent::TextureType::kNormal>(size_t index_, SRVHeapIndex dst_);
template
void Model::ChangeTexture<TextureComponent::TextureType::kEmissive>(size_t index_, SRVHeapIndex dst_);

