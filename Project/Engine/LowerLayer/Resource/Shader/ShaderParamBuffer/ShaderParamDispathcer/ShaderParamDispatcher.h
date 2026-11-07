#pragma once
#include "../../ShaderContext.h"


//外部
#include "../../../../../../Assets/Shared/ShaderParam.h"

#include "SimpleFreeList/SimpleFreeList.h"

class ShaderContext::ShaderParamDispatcher
{
public:

	struct LocalKey;

	template<ShaderParam::Type>
	struct ShaderParamTraits;

	ShaderParamDispatcher(NexusFieldProof proof_);

	//「シェーダーパラメーター配列」の
	//インデックスをかえす
	template<ShaderParam::Type type>
	uint32_t DispatchShaderParamID()
	{
		return freeListMap[(UINT)type].Distribute();
	}

	template<ShaderParam::Type type>
	void ImportShaderParamsBufferID(LocalKey key_,BufferUniqueID id_)
	{
		shaderParamBufferIdArr[(UINT)type] = id_;
		Logger::Log("Import "+ ShaderParamDispatcher::ShaderParamTraits<type>::kName + "ArrBuf: " + std::to_string(id_), "ShaderParamDispatcher.h");
	}


private:


	template<ShaderParam::Type type>
	void ReserveDispatchSize()
	{
		freeListMap[(UINT)type].Resize
		(
			ShaderParamTraits<type>::kReserveSize,
			ShaderParamTraits<type>::kName
		);
	}


	std::array<SimpleFreeList, (UINT)ShaderParam::Type::kCount> freeListMap;
	//書き込む必要があるので、シェーダーパラメーター配列のバッファIDは所持する
	std::array<BufferUniqueID, (UINT)ShaderParam::Type::kCount> shaderParamBufferIdArr;
};

struct ShaderContext::ShaderParamDispatcher::LocalKey
{

private:

	friend class ShaderParamBufferCreator;
	explicit LocalKey() = default;
};


template<>
struct ShaderContext::ShaderParamDispatcher::ShaderParamTraits<ShaderParam::Type::kGridLine>
{
	//シェーダーパラメータの割り当て上限数。同時に確保するバッファサイズ
	static constexpr UINT kReserveSize = 10;
	static inline const std::string kName = "GridLine";
	using dataType = ShaderParam::GridLineCPUGPU;
};
