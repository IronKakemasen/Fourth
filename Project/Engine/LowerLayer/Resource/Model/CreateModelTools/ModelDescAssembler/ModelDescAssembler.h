#pragma once
#include "../../ModelContext.h"
#include "../../ModelStructure/ModelDescription/ModelDescription.h"


//外部
#include "../../../../../../Assets/Shared/StructuredBufferModelData.h"
#include "../../../../../../Assets/Shared/ConstantBuffers.h"
#include "../../../Texture/TextureContext.h"


class ModelContext::ModelDescAssembler
{
	using ModelDescParts = std::tuple
	<
		std::vector<ConstantBuffers::PerDrawIndicesCPUGPU>,
		std::vector<StructuredBufferModelData::MaterialGPU>
	>;

public:

	ModelDescAssembler
	(
		NexusFieldProof proof_,
		ModelContext::ModelSlotAllocator* slotAllocator_,
		TextureContextDiplomat& textureContextDiplomat_
	);

	//モデルクラスのRenderStates以外のディスクリプションを作ってあげる
	ModelDescParts Assemble
	(
		std::string modelFileName_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& inputMaterials_
	);

private:

	//PerDrawIndicesを詰める
	std::vector<ConstantBuffers::PerDrawIndicesCPUGPU> PackPerDrawIndices
	(
		const std::vector<MeshDataID>& meshDataIDs_,
		size_t const kNumMeshData_
	);

	//引数のマテリアルデータをGPU仕様に変換する。
	//もし、中身が空だった場合は、そのモデル名に紐づけられているマテリアルデータを入力
	std::vector<StructuredBufferModelData::MaterialGPU> ConvertMaterialData
	(
		size_t const kNumMeshData_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materialsFromFile_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& inputMaterials
	);


	//TransformやMaterialのスロットを割り当てる
	ModelContext::ModelSlotAllocator* slotAllocator;
	
	//MaterialCPU -> materialGPUへ変換するため
	TextureContext::TextureLibrary* textureLib;

};


