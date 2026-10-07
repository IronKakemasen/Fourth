#pragma once

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
