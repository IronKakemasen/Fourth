#pragma once

#ifdef __cplusplus

#include "../../Engine/MiddleLayer/Math/Vector/Vector2.h"
#include "../../Engine/MiddleLayer/Math/Vector/Vector3.h"
#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"
#include "../../Engine/MiddleLayer/Math/Matrix/Matrix4x4.h"

namespace StructuredBufferCameraData
{
	struct CameraDataCPUGPU
	{		
		Matrix4x4 view;
		Matrix4x4 proj;
		Matrix4x4 viewProj;
		Vector4<float> worldPos;
		Vector4<float> lookDir;
	};

}

#else

struct CameraData
{
	float4x4 view;
	float4x4 proj;
	float4x4 viewProj;
	float4 worldPos;
	float4 lookDir;
};

struct CameraDataSrvArr
{
	uint cameraDataSrvIndex;
};



#endif