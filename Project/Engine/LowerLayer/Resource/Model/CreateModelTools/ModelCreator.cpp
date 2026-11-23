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

template<Model::MeshUpdateType type>
std::vector<std::unique_ptr<Model>> ModelContext::ModelCreator::Create
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	UINT const numCreate_,
	std::string const& modelName_
)
{
	static_assert
	(
		type != Model::MeshUpdateType::kCount,
		"Model::MeshUpdateType::KCountを選択してんじゃない ModelCreator.cpp"
	);

	//作成するモデルのユニーク
	std::vector<std::unique_ptr<Model>> modelUniques;
	modelUniques.reserve(numCreate_);

	for (UINT i = 0;i < numCreate_;++i)
	{
		//モデルの要素を組み立てる
		auto [modelConstants, meshletSize] = AssembleModelDescParts(modelFileName_);

		//マテリアルの入れ物を作成する
		//サブメッシュ分用意する
		std::vector<Materials> materials;
		materials.reserve(meshletSize.size());

		for (UINT k = 0;k < meshletSize.size();++k)
		{
			//モデルにマテリアルの入れ物を作成し、マテリアルIDを割り当てる
			materials.emplace_back(materialAttacher->CreateMaterials());
		}

		///一つのDescに詰める
		ModelDescription modelDesc
		(
			modelName_ + std::to_string(numCreate++),
			modelConstants,
			modelRenderStates_,
			meshletSize
		);

		///モデルクラスのインスタンス化
		modelUniques.emplace_back
		(
			std::make_unique<Model>
			(
				modelDesc, 
				std::move(materials)
			)
		);
	}

	//レンダーステートキャッシュに登録
	renderStatesCache.append_range(modelRenderStates_);

	return modelUniques;
}


void ModelContext::ModelCreator::InputMaterialStandard(std::string const& modelFileName_, Model& model_)
{
	auto const numMesh = model_.changeableParams.materialsContainer.size();

	//モデルのレンダーステートにMaterialStandardタイプがあるかチェック
#ifdef _DEBUG

	UINT passCnt{};
	for (auto const& renderState : model_.modelDesc.WatchRenderStates())
	{
		for (auto const& materialType : renderState.materialTypes)
		{
			if (materialType == Material::Type::kStandard) passCnt++;
		}
	}

	ErrorMessageOutput::Assert::DetectError
	(
		passCnt == numMesh,
		model_.WatchName() + ": MaterialStandardをレンダーステートに登録していないのに入力すな",
		fileName
	);

#endif // _DEBUG

	//モデルファイル名からマテリアルデータを拾う
	std::vector<Material::StandardGPU> src = modelDescAssembler->LoadModelMaterialData(modelFileName_);

	//データ入力
	for (size_t i = 0;i < numMesh;++i)
	{
		auto& dst = model_.changeableParams.materialsContainer[i];
		dst.Ref<Material::Type::kStandard>() = src[i];
	}
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
	std::string const& modelFileName_
)
{
	return modelDescAssembler->Assemble(modelFileName_);
}


template
std::vector<std::unique_ptr<Model>> ModelContext::ModelCreator::Create<Model::MeshUpdateType::kDynamic>
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	UINT const numCreate_,
	std::string const& modelName_
);

template
std::vector<std::unique_ptr<Model>> ModelContext::ModelCreator::Create<Model::MeshUpdateType::kStatic>
(
	std::string const& modelFileName_,
	std::vector<RenderState> const& modelRenderStates_,
	UINT const numCreate_,
	std::string const& modelName_
);
