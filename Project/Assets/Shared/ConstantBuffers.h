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
		kShaderParamArrSrvIndices

		, kCount
	};

	enum class RootConstantsBindSlots
	{
		kPerDrawIndices = ConstantBufferBindSlots::kCount,
		kPassConstants,
		kFinalColorBufferSrv,
		kShaderParamIndicesContainerIndex

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
	uint gCameraContainerIndex;
}

cbuffer ShaderParamArrSrvIndicesIndexCB : register(b6)
{
	uint gShaderParamArrSrvIndicesIndex;
}









ConstantBuffer<PerDrawIndices> gPerDrawIndices: register(b7);

ConstantBuffer<PassConstants> gPassConstants: register(b8);

cbuffer FinalColorBufferSrvCB : register(b9)
{
	uint gFinalColorBufferSrv;
}

cbuffer ShaderParamIndicesContainerIndexCB : register(b10)
{
	uint gShaderParamIndicesContainerIndex;
}


#endif

