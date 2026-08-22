#pragma once

#ifdef __cplusplus


namespace StaticSampler
{
    enum class SamplerState
    {
        kPointWrap,          
        kPointClamp,         
        kLinearWrap,         
        kLinearClamp,        
        kAnisotropicWrap,    
        kAnisotropicClamp


        ,kCount
    };

}


#else


SamplerState sampler_pointWrap             : register(s0);
SamplerState sampler_pointClamp            : register(s1);
SamplerState sampler_linearWrap            : register(s2);
SamplerState sampler_linearClamp           : register(s3);
SamplerState sampler_anisotropicWrap       : register(s4);
SamplerState sampler_anisotropicClamp      : register(s5);


#endif

