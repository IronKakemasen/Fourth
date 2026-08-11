#pragma once

#ifdef __cplusplus
#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"

namespace ConstantBuffers
{
	enum class ConstantBufferBindSlots
	{
		kMeshDataContainer,
		kTransformMatrixContainer

		, kCount
	};

	enum class RootConstantsBindSlots
	{
		kPerDrawIndices = ConstantBufferBindSlots::kCount


		,kCount
	};

	struct PerDrawIndicesCPUGPU
	{
		UINT modelDataID;
		UINT transformMatrixID;
	};


}


#else

struct PerDrawIndices
{
	uint modelDataID;
	uint transformMatrixID;
};


cbuffer ModelDataContainerIndexCB : register(b0)
{
	uint gModelDataContainerIndex;
}

cbuffer TransformMatrixContainerIndexCB : register(b1)
{
	uint gTransformMatrixContainerIndex;
}

ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b2);

#endif

