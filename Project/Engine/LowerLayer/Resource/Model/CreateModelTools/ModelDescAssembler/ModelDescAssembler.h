#pragma once
#include "../../ModelContext.h"
#include "../../ModelStructure/ModelDescription/ModelDescription.h"


//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../Texture/TextureContext.h"


class ModelContext::ModelDescAssembler
{
	using ModelDescSet = std::pair<std::vector<ModelDescription::Common>, std::vector<ModelDescription::Unique>>;

public:

	ModelDescAssembler
	(
		NexusFieldProof proof_,
		ModelContext::ModelSlotAllocator* slotAllocator_,
		TextureContextDiplomat& textureContextDiplomat_
	);

	//モデルクラスのRenderStates以外のディスクリプションを作ってあげる
	ModelDescSet Assemble
	(
		std::string modelFileName_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_
	);

private:

	//PerDrawIndicesのうち、モデル種共通のパラメーターを詰める
	std::vector<ModelDescription::Common> PackCommonData
	(
		const std::vector<MeshDataID>& meshDataIDs_,
		size_t const kNumMeshData_
	);

	//PerDrawIndicesのうち、モデルごとに所持するパラメーターを詰める
	std::vector<ModelDescription::Unique> PackUniqueData(size_t const kNumMeshData_);

	//引数のマテリアルデータをGPU仕様に変換する。
	//もし、中身が空だった場合は、そのモデル名に紐づけられているマテリアルデータを入力
	std::vector<StructuredBufferModelData::MaterialGPU> ConvertMaterialData
	(
		size_t const kNumMeshData_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_
	);


	//TransformやMaterialのスロットを割り当てる
	ModelContext::ModelSlotAllocator* slotAllocator;
	
	//MaterialCPU -> materialGPUへ変換するため
	TextureContext::TextureLibrary* textureLib;

};


