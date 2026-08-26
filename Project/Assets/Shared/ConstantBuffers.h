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
		kPerDrawIndices = ConstantBufferBindSlots::kCount,
		kPassBufferIndexRange

		,kCount
	};

	struct PerDrawIndicesCPUGPU
	{
		MeshDataID meshDataID;
		uint32_t transformMatrixID;
	};

	struct PassBufferIndexRangeCPUGPU
	{
		uint32_t offset;
		uint32_t numTextureUse;
	};

}


#else

struct PerDrawIndices
{
	uint meshDataID;
	uint transformMatrixID;
};

struct PassBufferIndexRange
{
	uint offset;
	uint numTextureUse;
};


cbuffer ModelDataContainerIndexCB : register(b0)
{
	uint gMeshDataIDDataContainerIndex;
}

cbuffer TransformMatrixContainerIndexCB : register(b1)
{
	uint gTransformMatrixContainerIndex;
}

ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b2);

ConstantBuffer<PassBufferIndexRange> gPassBufferIndexRange: register(b3);

#endif

