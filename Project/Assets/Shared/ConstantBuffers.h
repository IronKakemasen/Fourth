#pragma once

#ifdef __cplusplus
#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"

namespace ConstantBuffers
{
	enum class BindSlot
	{
		kMeshDataContainer,
		kTransformMatrixContainer

		, kCount
	};

}


#else


ConstantBuffer<uint> gModelDataContainerIndex: register(b0);
ConstantBuffer<uint> gTransformMatrixContainerIndex: register(b1);

#endif

