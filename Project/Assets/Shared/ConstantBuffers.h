#pragma once

#ifndef FOURTH_SHARED_CONSTANT_BUFFERS_H
#define FOURTH_SHARED_CONSTANT_BUFFERS_H

#ifdef __cplusplus
#include "../../Engine/Math/Vector/Vector4.h"

namespace ConstantBuffers
{
	enum class ConstantBufferBindSlots
	{
		kMeshDataContainer,
		kTransformMatrixContainer,
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

cbuffer TextureContainerIndexCB : register(b2)
{
	uint gTextureContainerIndex;
}

cbuffer PassRefBufferContainerIndexCB : register(b3)
{
	uint gPassRefBufferContainerIndex;
}

cbuffer CameraContainerIndexCB : register(b4)
{
	uint gCameraContainerSrvIndex;
}

cbuffer MaterialArrBufferSrvIndicesSrvIndexCB : register(b5)
{
	uint gMaterialArrBufferSrvIndicesSrvIndex;
}

cbuffer MaterialIDGroupArrBufferSrvCB : register(b6)
{
	uint gMaterialIDGroupArrBufferSrv;
}










ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b7);

ConstantBuffer<PassConstants> gPassConstants: register(b8);

cbuffer FinalColorBufferSrvCB : register(b9)
{
	uint gFinalColorBufferSrv;
}




#endif

#endif 