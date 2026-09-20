#pragma once

#ifdef __cplusplus
#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"

namespace ConstantBuffers
{
	enum class ConstantBufferBindSlots
	{
		kMeshDataContainer,
		kTransformMatrixContainer,
		kMaterialContainer,
		kTextureContainer,
		kPassRefBufferIndices

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
		uint32_t materialID;
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
	uint materialID;
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

cbuffer MaterialContainerIndexCB : register(b2)
{
	uint gMaterialContainerIndex;
}

cbuffer TextureContainerIndexCB : register(b3)
{
	uint gTextureContainerIndex;
}

ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b4);

ConstantBuffer<PassBufferIndexRange> gPassBufferIndexRange: register(b5);

#endif

