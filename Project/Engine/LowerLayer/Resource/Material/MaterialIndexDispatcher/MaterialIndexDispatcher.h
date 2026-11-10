#pragma once
#include "../MaterialContext.h"


//外部
#include "../../../../../Assets/Shared/Material.h"

#include "SimpleFreeList/SimpleFreeList.h"


class MaterialContext::MaterialIndexDispatcher
{

public:

	struct LocalKey;

	MaterialIndexDispatcher(NexusFieldProof proof_);

	//「シェーダーパラメーター配列」の
	//インデックスをかえす
	template<Material::Type type>
	uint32_t DispatchMaterialID()
	{
		return freeListMap[(UINT)type].Distribute();
	}

	template<Material::Type type>
	void ImportMaterialArrBufferID(LocalKey key_, BufferUniqueID id_)
	{
		materialArrBufferIdArr[(UINT)type] = id_;
		Logger::Log("Import " + Material::MaterialTypeTraits<type>::kName + "ArrBuf: " + std::to_string(id_), "MaterialIndexDispatcher.h");
	}

	void ImportMaterialIDGroupArrBufferID(LocalKey key_, BufferUniqueID id_);

private:

	//デバッグ用。ちゃんとReserveDispatchSize()が呼ばれたかチェック
	Material::Type typeSepuence = Material::Type(0);

	template<Material::Type type>
	void ReserveDispatchSize()
	{
		freeListMap[(UINT)type].Resize
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

	std::array<SimpleFreeList, (UINT)Material::kNumParamExists> freeListMap;
	//書き込む必要があるので、マテリアル配列のバッファIDは所持する
	std::array<BufferUniqueID, (UINT)Material::kNumParamExists> materialArrBufferIdArr;
	//各描画対象のマテリアルID群の配列のばっふぁID 
	BufferUniqueID materialIDGroupArrBufferID;

};

struct MaterialContext::MaterialIndexDispatcher::LocalKey
{

private:

	friend class MaterialBufferCreator;
	explicit LocalKey() = default;
};

