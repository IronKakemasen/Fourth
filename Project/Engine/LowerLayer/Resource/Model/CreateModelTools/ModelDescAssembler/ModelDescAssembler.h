#pragma once
#include "../ModelCreator.h"


//外部
//効率のため
#include "../../../Texture/TextureContext.h"


class ModelContext::ModelCreator::ModelDescAssembler
{

public:

	ModelDescAssembler
	(
		NexusFieldProof proof_,
		ModelSlotAllocator& slotAllocator_,
		TextureContextDiplomat& textureContextDiplomat_
	);

	//モデルクラスのRenderStates以外のディスクリプションを作ってあげる
	ModelDescParts Assemble
	(
		std::string const& modelFileName_
	);

private:

	//modelConstantsを詰める
	std::vector<ConstantBuffers::ModelConstantsCPUGPU> PackModelConstants
	(
		const std::vector<MeshDataID>& meshDataIDs_,
		size_t const kNumMeshData_
	);

	//引数のマテリアルデータをGPU仕様に変換する。
	//もし、中身が空だった場合は、そのモデル名に紐づけられているマテリアルデータを入力
	std::vector<Material::StandardGPU> ConvertMaterialData
	(
		size_t const kNumMeshData_,
		std::vector<Material::StandardCPU> const& materialsFromFile_
	);


	//TransformやMaterialのスロットを割り当てる
	ModelContext::ModelSlotAllocator& slotAllocator;
	
	//MaterialCPU -> materialGPUへ変換するため
	TextureContext::TextureLibrary* textureLib;

};


