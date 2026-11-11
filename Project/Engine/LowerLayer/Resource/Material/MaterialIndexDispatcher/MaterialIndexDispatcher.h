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

	//マテリアル配列のインデックス群配列(Material::MaterialIndexGroupCPUGPU)の
	//添え字のフリーリスト
	SimpleFreeList materialIDFreeList;


};
