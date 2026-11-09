#pragma once
#include "../MaterialContext.h"


//外部
#include "../../../../../../Assets/Shared/Material.h"

#include "SimpleFreeList/SimpleFreeList.h"


class MaterialContext::MaterialIndexDispatcher
{

public:

	struct LocalKey;

	MaterialIndexDispatcher(NexusFieldProof proof_);

	//「シェーダーパラメーター配列」の
	//インデックスをかえす
	template<Material::Type type>
	uint32_t DispatchShaderParamID()
	{
		return freeListMap[(UINT)type].Distribute();
	}

	template<Material::Type type>
	void ImportShaderParamsBufferID(LocalKey key_, BufferUniqueID id_)
	{
		shaderParamBufferIdArr[(UINT)type] = id_;
		Logger::Log("Import " + Material::MaterialTypeTraits<type>::kName + "ArrBuf: " + std::to_string(id_), "ShaderParamDispatcher.h");
	}

private:


	template<Material::Type type>
	void ReserveDispatchSize()
	{
		freeListMap[(UINT)type].Resize
		(
			Material::MaterialTypeTraits<type>::kReserveSize,
			Material::MaterialTypeTraits<type>::kName
		);
	}


	std::array<SimpleFreeList, (UINT)Material::Type::kCount> freeListMap;
	//書き込む必要があるので、シェーダーパラメーター配列のバッファIDは所持する
	std::array<BufferUniqueID, (UINT)Material::Type::kCount> shaderParamBufferIdArr;
};

struct MaterialContext::MaterialIndexDispatcher::LocalKey
{

private:

	friend class MaterialBufferCreator;
	explicit LocalKey() = default;
};

