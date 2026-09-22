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

ModelContext::ModelDescAssembler::ModelDescAssembler
(
	NexusFieldProof proof_,
	ModelContext::ModelSlotAllocator* slotAllocator_,
	TextureContextDiplomat& textureContextDiplomat_
):slotAllocator(slotAllocator_)
{
	//テクスチャライブラリーを借りる
	auto& toolLender = textureContextDiplomat_.Access<TextureContext::ToolLender>();
	TextureContext::ToolLender::LicenceType<TextureContext::TextureLibrary> licence;
	textureLib = &toolLender.Lend<TextureContext::TextureLibrary>(licence);

}

ModelContext::ModelDescAssembler::ModelDescParts ModelContext::ModelDescAssembler::Assemble
(
	std::string modelFileName_,
	std::vector<MaterialCPU> const& inputMaterials_
)
{
	//modelDataLibraryにアクセス
	auto& modelDataLibrary = slotAllocator->AccessModelDataLibrary(ModelContext::ModelSlotAllocator::HandleLicence{});
	
	//モデルファイル名からサブメッシュ分含む、メッシュデータのユニークIDを検索
	std::vector<MeshDataID> const& meshDataIDs = modelDataLibrary.Find<MeshDataID>(modelFileName_);
	//マテリアルも同様
	std::vector<MaterialCPU> const& materialsFromFile = modelDataLibrary.Find<MaterialCPU>(modelFileName_);

	//サブメッシュ含む、メッシュの総数
	size_t const kNumMeshData = meshDataIDs.size();

	return ModelDescParts
	(
		PackPerDrawIndices(meshDataIDs, kNumMeshData),
		ConvertMaterialData(kNumMeshData, materialsFromFile, inputMaterials_)
	);

}

std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> ModelContext::ModelDescAssembler::PackPerDrawIndices
(
	const std::vector<MeshDataID>& meshDataIDs_,
	size_t const kNumMeshData_
)
{
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> perDrawIndices;

	auto const licence = ModelContext::ModelSlotAllocator::AllocateLicence{};

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		//メッシュデータIDを割り当てる
		ConstantBuffers::PerDrawIndicesCPUGPU perDrawIndex;
		perDrawIndex.meshDataID = meshDataIDs_[i];

		//トランスフォームIDを割り当てる
		perDrawIndex.transformMatrixID =
			slotAllocator->AllocateSlot<ModelContext::ModelSlotAllocator::TransformMatrixSlot>(licence);

		//マテリアルIDを割り当てる
		perDrawIndex.materialID =
			slotAllocator->AllocateSlot<ModelContext::ModelSlotAllocator::MaterialSlot>(licence);

		perDrawIndices.emplace_back(std::move(perDrawIndex));
	}

	return perDrawIndices;
}


std::vector<MaterialGPU> ModelContext::ModelDescAssembler::ConvertMaterialData
(
	size_t const kNumMeshData_,
	std::vector<MaterialCPU> const& materialsFromFile_,
	std::vector<MaterialCPU> const& inputMaterials
)
{
	//テクスチャファイルパスから、テクスチャファイル名へ変換
	std::vector<MaterialGPU> materialGPUContainer;

	//サブメッシュ分も拡張する
	materialGPUContainer.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		auto& dst = materialGPUContainer[i];

		//データの手動入力があればそちらが優先
		if (i < inputMaterials.size())
		{
			auto const& src = inputMaterials[i];

			if (src.albedoTexture.size() > 0)	dst.albedoTexture	= textureLib->Export(src.albedoTexture);
			if (src.normalTexture.size() > 0)	dst.normalTexture	= textureLib->Export(src.normalTexture);
			if (src.emissiveTexture.size() > 0) dst.emissiveTexture = textureLib->Export(src.emissiveTexture);

			if (src.roughness != kInvalid)	dst.roughness	= src.roughness;
			if (src.metallic != kInvalid)	dst.metallic	= src.metallic;

		}

		//手動入力で満たされなかった部分を、モデル名に紐づけられているデータから入力する
		if (i < materialsFromFile_.size())
		{
			auto const& src = materialsFromFile_[i];

			if (dst.albedoTexture == kInvalid && src.albedoTexture.size() > 0)
				dst.albedoTexture = textureLib->Export(src.albedoTexture);

			if (dst.normalTexture == kInvalid && src.normalTexture.size() > 0)
				dst.normalTexture = textureLib->Export(src.normalTexture);

			if (dst.emissiveTexture == kInvalid && src.emissiveTexture.size() > 0)	
				dst.emissiveTexture = textureLib->Export(src.emissiveTexture);

			if (dst.roughness == kInvalid && src.roughness != kInvalid)
				dst.roughness	= src.roughness;

			if (dst.metallic == kInvalid && src.metallic != kInvalid)	
				dst.metallic	= src.metallic;
		}

		//手動入力もなくソースも無ければ、適当な値を入れておく
		{
			if (dst.albedoTexture == kInvalid)dst.albedoTexture = textureLib->Export("white4x4_albedo");
			if (dst.roughness == kInvalid)dst.roughness = 0.25f;
			if (dst.metallic == kInvalid )dst.metallic = 0.9f;
		}
	}

	return materialGPUContainer;
}


