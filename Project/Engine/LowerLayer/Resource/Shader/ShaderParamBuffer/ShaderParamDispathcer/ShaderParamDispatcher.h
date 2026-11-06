#pragma once
#include "../../ShaderContext.h"


//外部
#include "../../../../../../Assets/Shared/ShaderParam.h"

#include "SimpleFreeList/SimpleFreeList.h"

class ShaderContext::ShaderParamDispatcher
{
public:

	template<ShaderParam::Type>
	struct ShaderParamTraits;

	ShaderParamDispatcher(NexusFieldProof proof_);


	template<ShaderParam::Type type>
	uint32_t Dispatch()
	{
		return freeListMap[(UINT)type].Distribute();
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


	SimpleFreeList freeListMap[(UINT)ShaderParam::Type::kCount];

};

template<>
struct ShaderContext::ShaderParamDispatcher::ShaderParamTraits<ShaderParam::Type::kGridLine>
{
	//シェーダーパラメータの割り当て上限数。同時に確保するバッファサイズ
	static constexpr UINT kReserveSize = 10;
	static inline const std::string kName = "GridLine";
	using dataType = ShaderParam::GridLineCPUGPU;
};
