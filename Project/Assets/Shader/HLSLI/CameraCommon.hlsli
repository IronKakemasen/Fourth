#pragma once

#include "../../Shared/StructuredBufferCameraData.h"
#include "../../Shared/ConstantBuffers.h"


CameraData AccessCamera(uint inedx_)
{
    StructuredBuffer<CameraData> cameraDataContainer = ResourceDescriptorHeap[gCameraContainerSrvIndex];

    return cameraDataContainer[inedx_];
}
