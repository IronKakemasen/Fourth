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
		kCameraContainer,
		kMaterialArrBufferSrvIndicesSrvIndex,
		kMaterialIDGroupArrBufferSrv

		, kCount
	};

	enum class RootConstantsBindSlots
	{
		kPerDrawIndices = ConstantBufferBindSlots::kCount,
		kPassConstants,
		kFinalColorBufferSrv,
		kMaterialIDGroupContainerIndex

		,kCount
	};


	constexpr uint8_t Num32BitValuesTable(RootConstantsBindSlots const slot_)
	{
		static UINT const numRootConstants = (UINT)RootConstantsBindSlots::kCount - (UINT)ConstantBufferBindSlots::kCount;
		UINT dstIndex = (UINT)slot_ - (UINT)ConstantBufferBindSlots::kCount;
		
		static constexpr uint8_t table[numRootConstants]
		{
			3,2,1,1
		};

		return table[dstIndex];
	}


	struct PerDrawIndicesCPUGPU
	{
		MeshDataID meshDataID;
		UINT transformMatrixID;
		UINT materialID;
	};

	struct PassConstantsCPUGPU
	{
		uint32_t refBufferOffset{};
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
	uint refBufferOffset;
	uint cameraOffset;
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
	uint gCameraContainerSrvIndex;
}

cbuffer MaterialArrBufferSrvIndicesSrvIndexCB : register(b6)
{
	uint gMaterialArrBufferSrvIndicesSrvIndex;
}

cbuffer MaterialIDGroupArrBufferSrvCB : register(b7)
{
	uint gMaterialIDGroupArrBufferSrv;
}










ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b8);

ConstantBuffer<PassConstants> gPassConstants: register(b9);

cbuffer FinalColorBufferSrvCB : register(b10)
{
	uint gFinalColorBufferSrv;
}

cbuffer MaterialIDGroupContainerIndexCB : register(b11)
{
	uint gMaterialIDGroupContainerIndex;
}


#endif

