#include "PreCompileHeader.h"
#include "ModelCreator.h"
#include "ModelDescAssembler/ModelDescAssembler.h"

//外部
#include "../../Material/MaterialContextDiplomat/MaterialContextDiplomat.h"
#include "../../Material/MaterialContextDiplomat/MaterialToolLender/MaterialToolLender.h"
#include "../../Material/MaterialContextDiplomat/MaterialToolLender/MaterialToolLenderLicences.h"
#include "../../Material/MaterialAttacher/MaterialAttacher.h"


namespace
{
	auto const fileName = "ModelCreator.cpp";
}

using namespace StructuredBufferModelData;

ModelContext::ModelCreator::ModelCreator
(
	NexusFieldProof proof_,
	ModelSlotAllocator& slotAllocator_,
	TextureContextDiplomat& textureContextDiplomat_,
	MaterialContextDiplomat& materialContextDiplomat_
) 
{
	modelDescAssembler = std::make_unique<ModelDescAssembler>(proof_, slotAllocator_, textureContextDiplomat_);

	//materialAttacherを借りる
	auto& materialToolLender = materialContextDiplomat_.Access<MaterialContext::ToolLender>();
	MaterialContext::ToolLender::LicenceType<MaterialContext::MaterialAttacher> licence;
	materialAttacher = &materialToolLender.Lend<MaterialContext::MaterialAttacher>(licence);

}

ModelContext::ModelCreator::~ModelCreator()
{

}

template<Model::Type modelType>
std::vector<std::unique_ptr<Model>> ModelContext::ModelCreator::Create
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	std::vector<Material::StandardCPU> const& materials_,
	UINT const numCreate_,
	std::string const& modelName_
)
{
	static_assert
	(
		modelType != Model::Type::kCount,
		"Model::Type::KCountを選択してんじゃない ModelCreator.h"
	);

	//作成するモデルのユニーク
	std::vector<std::unique_ptr<Model>> modelUniques;
	modelUniques.reserve(numCreate_);

	for (UINT i = 0;i < numCreate_;++i)
	{
		//モデルの要素を組み立てる
		auto [perDrawIndices, materialsGPU, meshletSize] = AssembleModelDescParts(modelFileName_, materials_);

		//マテリアルの入れ物を作成し、デフォルトでMaterial::StandardGPUをアタッチする
		//サブメッシュ分用意する
		std::vector<Materials> materials;
		materials.reserve(meshletSize.size());

		for (UINT k = 0;k < meshletSize.size();++k)
		{
			//モデルにマテリアルの入れ物を作成し、マテリアルIDを割り当てる
			materials.emplace_back(materialAttacher->CreateMaterials());
			//Material::StandardGPUをアタッチする
			materialAttacher->Attach<Material::Type::kStandard>(materials[k]);

			//Material::StandardGPUの値をコピーする
			materials[k].Ref<Material::Type::kStandard>() = materialsGPU[k];

			//描画対象ごとルートコンスタンツの一つ、マテリアルIDを記録
			perDrawIndices[k].materialID = materials[k].materialID;
		}

		///一つのDescに詰める
		ModelDescription modelDesc
		(
			modelName_ + std::to_string(numCreate++),
			perDrawIndices,
			modelRenderStates_,
			meshletSize
		);

		///モデルクラスのインスタンス化
		modelUniques.emplace_back
		(
			std::make_unique<Model>
			(
				modelType, 
				modelDesc, 
				std::move(materials)
			)
		);
	}

	//レンダーステートキャッシュに登録
	renderStatesCache.append_range(modelRenderStates_);

	return modelUniques;
}


std::vector<RenderState>const& ModelContext::ModelCreator::WatchRenderStateCache(AgentKey key_)const
{
	return renderStatesCache;
}

void ModelContext::ModelCreator::DeleteRenderStateCache(NexusFieldProof proof_ , AgentKey key_)
{
	renderStatesCache.clear();
	renderStatesCache.shrink_to_fit();
}


ModelContext::ModelCreator::ModelDescParts ModelContext::ModelCreator::AssembleModelDescParts
(
	std::string const& modelFileName_,
	std::vector<Material::StandardCPU> const& inputMaterials_
)
{
	return modelDescAssembler->Assemble(modelFileName_, inputMaterials_);
}


template
std::vector<std::unique_ptr<Model>> ModelContext::ModelCreator::Create<Model::Type::kDynamic>
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	std::vector<Material::StandardCPU> const& materials_,
	UINT const numCreate_,
	std::string const& modelName_
);

template
std::vector<std::unique_ptr<Model>> ModelContext::ModelCreator::Create<Model::Type::kStatic>
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	std::vector<Material::StandardCPU> const& materials_,
	UINT const numCreate_,
	std::string const& modelName_
);
