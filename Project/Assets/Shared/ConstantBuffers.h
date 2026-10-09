#pragma once

#ifdef __cplusplus
#include "../../Engine/Math/Vector/Vector4.h"

namespace ConstantBuffers
{
	enum class ConstantBufferBindSlots
	{
		kMeshDataContainer,
		kTransformMatrixContainer,
		kMaterialContainer,
		kTextureContainer,
		kPassRefBufferIndices,
		kCameraContainer

		, kCount
	};

	enum class RootConstantsBindSlots
	{
		kPerDrawIndices = ConstantBufferBindSlots::kCount,
		kPassConstants,
		kFinalColorBufferSrv

		,kCount
	};


	constexpr uint8_t Num32BitValuesTable(RootConstantsBindSlots const slot_)
	{
		static UINT const numRootConstants = (UINT)RootConstantsBindSlots::kCount - (UINT)ConstantBufferBindSlots::kCount;
		UINT dstIndex = (UINT)slot_ - (UINT)ConstantBufferBindSlots::kCount;
		
		static constexpr uint8_t table[numRootConstants]
		{
			3,2,1
		};

		return table[dstIndex];
	}


	struct PerDrawIndicesCPUGPU
	{
		MeshDataID meshDataID;
		BufferUniqueID transformMatrixID;
		BufferUniqueID materialID;
	};

	struct PassConstantsCPUGPU
	{
		uint32_t refBuffferOffset{};
		uint32_t cameraOffset{};
	};
}


#else

struct PerDrawIndices
{
	uint meshDataID;
	uint transformMatrixID;
	uint materialID;
};

struct PassConstants
{
	uint refBuffferOffset;
	uint numRefBuffers;
	uint cameraOffset;
	uint numCameras;
};


cbuffer MeshDataIndexContainerCB : register(b0)
{
	uint gMeshDataIndexContainer;
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

cbuffer PassRefBufferContainerIndexCB : register(b4)
{
	uint gPassRefBufferContainerIndex;
}

cbuffer CameraContainerIndexCB : register(b5)
{
	uint gCameraContainerIndex;
}


ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b6);

ConstantBuffer<PassConstants> gPassConstants: register(b7);

cbuffer FinalColorBufferSrvCB : register(b8)
{
	uint gFinalColorBufferSrv;
}


#endif

