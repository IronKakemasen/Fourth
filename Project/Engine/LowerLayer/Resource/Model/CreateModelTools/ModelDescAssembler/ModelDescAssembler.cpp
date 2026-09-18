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
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> preDrawindices;
	preDrawindices.resize(kNumMeshData_);

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

		preDrawindices.emplace_back(std::move(perDrawIndex));
	}

	return preDrawindices;
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
		//データの手動入力があれば
		if (i < inputMaterials.size())
		{
			materialGPUContainer[i].albedoTexture = textureLib->Export(inputMaterials[i].albedoTexture);
			materialGPUContainer[i].normalTexture = textureLib->Export(inputMaterials[i].normalTexture);
			materialGPUContainer[i].emissiveTexture = textureLib->Export(inputMaterials[i].emissiveTexture);
			materialGPUContainer[i].roughness = inputMaterials[i].roughness;
			materialGPUContainer[i].metallic = inputMaterials[i].metallic;
		}
		//入力されてないなら、モデル名に紐づけられているデータから入力する
		else
		{
			if (i < materialsFromFile_.size())
			{
				materialGPUContainer[i].albedoTexture = textureLib->Export(materialsFromFile_[i].albedoTexture);
				materialGPUContainer[i].normalTexture = textureLib->Export(materialsFromFile_[i].normalTexture);
				materialGPUContainer[i].emissiveTexture = textureLib->Export(materialsFromFile_[i].emissiveTexture);
				materialGPUContainer[i].roughness = materialsFromFile_[i].roughness;
				materialGPUContainer[i].metallic = materialsFromFile_[i].metallic;
			}
			//ファイルからフェッチしたマテリアルデータがないならnoDataを入れておく
			else
			{
				materialGPUContainer[i].albedoTexture = textureLib->Export(kNoDataAlbedoTex);
				materialGPUContainer[i].normalTexture = textureLib->Export(kNoDataNormalTex);
				materialGPUContainer[i].emissiveTexture = textureLib->Export(kNoDataEmissiveTex);
				materialGPUContainer[i].roughness = 0.1f;
				materialGPUContainer[i].metallic = 1.0f;
			}

		}
	}

	return materialGPUContainer;
}


