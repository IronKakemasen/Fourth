#pragma once

#include "../../Shared/StructuredBufferModelData.h"
#include "../../Shared/Material.h"
#include "../../Shared/ConstantBuffers.h"

struct MS_StandardOutput
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : POSITION0;

};

uint3 UnpackPrimitiveIndex(uint packedIndex_)
{
    return uint3
    (
        packedIndex_ & 0x3FF,
        (packedIndex_ >> 10) & 0x3FF,
        (packedIndex_ >> 20) & 0x3FF
    );
}

MaterialStandard LoadMaterialStandard(uint materialID_)
{
    StructuredBuffer<MaterialArrBufferSrvIndexGroup> srvGroupBuffer =
        ResourceDescriptorHeap[gMaterialArrBufferSrvIndicesSrvIndex];

    StructuredBuffer<MaterialIndexGroup> indexGroupArr =
        ResourceDescriptorHeap[gMaterialIDGroupArrBufferSrv];

    StructuredBuffer<MaterialStandard> standardArr =
        ResourceDescriptorHeap[srvGroupBuffer[0].standardSrv];

    MaterialIndexGroup indexGroup = indexGroupArr[materialID_];

    return standardArr[indexGroup.standardIndex];
}

float4 SampleColor(Texture2D<float4> texture_,uint samplerState_,float2 texcoord_)
{
    float4 sampledColor;
    
    if (samplerState_ == 0)
    {
        sampledColor = texture_.Sample(sampler_pointWrap, texcoord_);
    }
    else if (samplerState_ == 1)
    {
        sampledColor = texture_.Sample(sampler_pointClamp, texcoord_);
    }
    else if (samplerState_ == 2)
    {
        sampledColor = texture_.Sample(sampler_linearWrap, texcoord_);
    }
    else if (samplerState_ == 3)
    {
        sampledColor = texture_.Sample(sampler_linearClamp, texcoord_);
    }
    else if (samplerState_ == 4)
    {
        sampledColor = texture_.Sample(sampler_anisotropicWrap, texcoord_);
    }
    else if (samplerState_ == 5)
    {
        sampledColor = texture_.Sample(sampler_anisotropicClamp, texcoord_);
    }

    return sampledColor;
}
