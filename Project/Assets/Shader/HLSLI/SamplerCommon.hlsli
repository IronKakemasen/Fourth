#pragma once
#include "../../Shared/StaticSampler.h"


float4 SampleColor(Texture2D<float4> texture_, uint samplerState_, float2 texcoord_)
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
