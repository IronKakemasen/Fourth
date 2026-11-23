#include "PreCompileHeader.h"
#include "ModelDescAssembler.h"
#include "../../CreateModelTools/ModelSlotAllocator/ModelDataLibrary/ModelDataLibrary.h"


//外部
#include "../../../Texture/TextureContextDiplomat/TextureContextDiplomat.h"
#include "../../../Texture/TextureContextDiplomat/TextureContextToolLender/TextureContextToolLender.h"
#include "../../../Texture/TextureContextDiplomat/TextureContextToolLender/TextureContextToolLenderLicences.h"
#include "../../../Texture/TextureLibrary/TextureLibrary.h"


using namespace StructuredBufferModelData;
using namespace ProjectConfig::Texture;

ModelContext::ModelCreator::ModelDescAssembler::ModelDescAssembler
(
	NexusFieldProof proof_,
	ModelSlotAllocator& slotAllocator_,
	TextureContextDiplomat& textureContextDiplomat_
):slotAllocator(slotAllocator_)
{
	//テクスチャライブラリーを借りる
	auto& toolLender = textureContextDiplomat_.Access<TextureContext::ToolLender>();
	TextureContext::ToolLender::LicenceType<TextureContext::TextureLibrary> licence;
	textureLib = &toolLender.Lend<TextureContext::TextureLibrary>(licence);

}

ModelContext::ModelCreator::ModelDescParts ModelContext::ModelCreator::ModelDescAssembler::Assemble
(
	std::string const& modelFileName_
)
{
	//modelDataLibraryにアクセス
	auto& modelDataLibrary = slotAllocator.AccessModelDataLibrary(ModelContext::ModelSlotAllocator::HandleLicence{});
	
	//モデルファイル名からサブメッシュ分含む、
	//メッシュデータのユニークID、メッシュレットのサイズを検索
	auto const& modelData = modelDataLibrary.Find(modelFileName_);

	//サブメッシュ含む、メッシュの総数
	size_t const kNumMeshData = modelData.meshDataID.size();

	return ModelDescParts
	(
		PackModelConstants(modelData.meshDataID, kNumMeshData),
		modelData.meshletSize
	);


}

std::vector<Material::StandardGPU> ModelContext::ModelCreator::ModelDescAssembler::LoadModelMaterialData(std::string const& modelFileName_)
{
	//modelDataLibraryにアクセス
	auto& modelDataLibrary = slotAllocator.AccessModelDataLibrary(ModelContext::ModelSlotAllocator::HandleLicence{});
	//マテリアルデータを検索
	auto const& modelData = modelDataLibrary.Find(modelFileName_);

	//サブメッシュ含む、メッシュの総数
	size_t const kNumMeshData = modelData.meshDataID.size();

	return ConvertMaterialData(kNumMeshData, modelData.materialCPU);
}


std::vector<ConstantBuffers::ModelConstantsCPUGPU> ModelContext::ModelCreator::ModelDescAssembler::PackModelConstants
(
	const std::vector<MeshDataID>& meshDataIDs_,
	size_t const kNumMeshData_
)
{
	std::vector<ConstantBuffers::ModelConstantsCPUGPU> modelConstants;

	auto const licence = ModelContext::ModelSlotAllocator::AllocateLicence{};

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		//メッシュデータIDを割り当てる
		ConstantBuffers::ModelConstantsCPUGPU perDrawIndex;
		perDrawIndex.meshDataID = meshDataIDs_[i];

		//トランスフォームIDを割り当てる
		perDrawIndex.transformMatrixID =
			slotAllocator.AllocateSlot<ModelContext::ModelSlotAllocator::TransformMatrixSlot>(licence);

		modelConstants.emplace_back(std::move(perDrawIndex));
	}

	return modelConstants;
}


std::vector<Material::StandardGPU> ModelContext::ModelCreator::ModelDescAssembler::ConvertMaterialData
(
	size_t const kNumMeshData_,
	std::vector<Material::StandardCPU> const& materialsFromFile_
)
{
	//テクスチャファイルパスから、テクスチャファイル名へ変換
	std::vector<Material::StandardGPU> materialGPUContainer;

	//サブメッシュ分も拡張する
	materialGPUContainer.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		auto& dst = materialGPUContainer[i];

		//ソースが無いケースのために適当なデフォルト値を入れておく
		//あえて入れていないパラメータは、hlsl側でセンチネルとしての値が埋め込まれているので触らんように
		{
			if (dst.albedoTexture == kInvalid)
				dst.albedoTexture = textureLib->Export("white4x4_albedo");

			//割とおきにな値
			dst.roughness = 0.25f;
			dst.metallic = 0.9f;
			dst.baseColor = { 1.0f,1.0f,1.0f,1.0f };
		}


		//モデル名に紐づけられているデータから入力する
		if (i < materialsFromFile_.size())
		{
			auto const& src = materialsFromFile_[i];

			if (src.albedoTexture.size() > 0)
				dst.albedoTexture   = textureLib->Export(src.albedoTexture);

			if (src.normalTexture.size() > 0)
				dst.normalTexture   = textureLib->Export(src.normalTexture);

			if (src.emissiveTexture.size() > 0)	
				dst.emissiveTexture = textureLib->Export(src.emissiveTexture);

			if (src.roughness != kInvalid)   dst.roughness = src.roughness;

			if (src.metallic != kInvalid)    dst.metallic  = src.metallic;

			if (src.baseColor.x != kInvalid) dst.baseColor = src.baseColor;

		}

	}

	return materialGPUContainer;
}


