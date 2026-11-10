#pragma once
#include "../MaterialContext.h"


//外部
#include "../../../../../Assets/Shared/Material.h"

#include "SimpleFreeList/SimpleFreeList.h"


class MaterialContext::MaterialIndexDispatcher
{

public:

	MaterialIndexDispatcher(NexusFieldProof proof_);

	//マテリアルIDを返す
	UINT DispatchMaterialID();

	//「マテリアル配列」のインデックスをかえす
	template<Material::Type type>
	uint32_t DispatchMaterialArrIndex()
	{
		return materialArrIndexFreeList[(UINT)type].Distribute();
	}

	template<Material::Type type>
	void ImportMaterialArrBufferIndex(BufferUniqueID id_)
	{
		materialArrBufferIdArr[(UINT)type] = id_;
		Logger::Log("Import " + Material::MaterialTypeTraits<type>::kName + "ArrBuf: " + std::to_string(id_), "MaterialIndexDispatcher.h");
	}

	void ImportMaterialIDGroupArrBufferID(BufferUniqueID id_);

private:

	//デバッグ用。ちゃんとReserveDispatchSize()が呼ばれたかチェック
	Material::Type typeSepuence = Material::Type(0);

	template<Material::Type type>
	void ReserveMaterialArrDispatchSize()
	{
		materialArrIndexFreeList[(UINT)type].Resize
		(
			Material::MaterialTypeTraits<type>::kReserveSize,
			Material::MaterialTypeTraits<type>::kName
		);

		ErrorMessageOutput::Assert::DetectError
		(
			typeSepuence == type,
			"ShaderParamArrバッファの作成順序がおかしい",
			"MaterialIndexDispatcher.h"
		);

		//デバッグ
		typeSepuence = Material::Type((UINT)typeSepuence + 1);

	}

	//マテリアル配列のフリーリスト
	std::array<SimpleFreeList, (UINT)Material::kNumParamExists> materialArrIndexFreeList;
	//書き込む必要があるので、マテリアル配列のバッファのインデックスは所持する
	std::array<BufferUniqueID, (UINT)Material::kNumParamExists> materialArrBufferIdArr;

	//マテリアル配列のインデックス群配列(Material::MaterialIndexGroupCPUGPU)の
	//添え字のフリーリスト
	SimpleFreeList materialIDFreeList;

	//各描画対象のマテリアル配列インデックス群配列のバッファID 
	BufferUniqueID materialIDGroupArrBufferID;

};
