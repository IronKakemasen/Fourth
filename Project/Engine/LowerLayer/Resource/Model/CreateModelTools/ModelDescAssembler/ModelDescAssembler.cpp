#include "PreCompileHeader.h"
#include "ModelDescAssembler.h"
#include "../../CreateModelTools/ModelSlotAllocator/MeshDataIDLibrary/MeshDataIDLibrary.h"


//外部
#include "../../../Texture/TextureContextDiplomat/TextureContextDiplomat.h"
#include "../../../Texture/TextureContextDiplomat/TextureContextToolLender/TextureContextToolLender.h"
#include "../../../Texture/TextureContextDiplomat/TextureContextToolLender/TextureContextToolLenderLicences.h"
#include "../../../Texture/TextureLibrary/TextureLibrary.h"

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

using namespace StructuredBufferModelData;

ModelContext::ModelDescAssembler::ModelDescSet ModelContext::ModelDescAssembler::Assemble
(
	std::string modelFileName_,
	std::vector<MaterialCPU> const& materials_
)
{
	auto& meshDataIDLib = slotAllocator->AccessMeshDataIDLibrary(ModelContext::ModelSlotAllocator::HandleLicence{});
	
	//モデルファイル名からメッシュデータのユニークIDを検索
	const std::vector<MeshDataID>& meshDataIDs = meshDataIDLib.Find(modelFileName_);
	
	//サブメッシュ含む、メッシュの総数
	size_t const kNumMeshData = meshDataIDs.size();

	return std::make_pair(PackCommonData(meshDataIDs, kNumMeshData), PackUniqueData(kNumMeshData));
}

std::vector<ModelDescription::Common> ModelContext::ModelDescAssembler::PackCommonData
(
	const std::vector<MeshDataID>& meshDataIDs_,
	size_t const kNumMeshData_
)
{

	std::vector<ModelDescription::Common> commons;
	commons.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		ModelDescription::Common common;
		common.meshDataID = meshDataIDs_[i];

		commons[i] = std::move(common);
	}

	return commons;
}

std::vector<ModelDescription::Unique> ModelContext::ModelDescAssembler::PackUniqueData(size_t const kNumMeshData_)
{
	std::vector<ModelDescription::Unique> uniques;
	uniques.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		
		ModelDescription::Unique unique;
		auto const licence = ModelContext::ModelSlotAllocator::AllocateLicence{};


		//トランスフォームIDを割り当てる
		unique.dispatchedTransformedMatrixID =
			slotAllocator->AllocateSlot<ModelContext::ModelSlotAllocator::TransformMatrixSlot>(licence);

		//マテリアルIDを割り当てる
		unique.dispatchedMaterialID =
			slotAllocator->AllocateSlot<ModelContext::ModelSlotAllocator::MaterialSlot>(licence);

		uniques[i] = std::move(unique);

	}

	return uniques;
}

std::vector<MaterialGPU> ModelContext::ModelDescAssembler::ConvertMaterialData
(
	size_t const kNumMeshData_,
	std::vector<MaterialCPU> const& materials_
)
{
	//テクスチャファイルパスから、テクスチャファイル名へ変換
	std::vector<MaterialGPU> materialGPUContainer;

	//送られてきたデータのサイズ
	auto const sizeOfSrc = materials_.size();

	materialGPUContainer.resize(kNumMeshData_);

	for (size_t i = 0;i < kNumMeshData_;++i)
	{
		//データが入力されているのなら
		if (i < sizeOfSrc)
		{
			materialGPUContainer[i].albedoTexture = textureLib->Export(materials_[i].albedoTexture);
			materialGPUContainer[i].normalTexture = textureLib->Export(materials_[i].normalTexture);
			materialGPUContainer[i].emissiveTexture = textureLib->Export(materials_[i].emissiveTexture);
			materialGPUContainer[i].roughness = materials_[i].roughness;
			materialGPUContainer[i].metallic = materials_[i].metallic;
		}
		//入力されてないなら、モデル名に紐づけられているデータから入力する
		else
		{

		}
	}

	return materialGPUContainer;
}


