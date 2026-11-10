#pragma once

#ifdef __cplusplus

#include "StaticSampler.h"
#include "../../Engine/Math/Vector/Vector4.h"

namespace Material
{
    enum class Type
    {
        kStandard,
        kGridLine,
        
        
        
        
       
        kOffscreen,
        kNone,
        kCount

    };

    static constexpr UINT kNumParamExists = 2;

    template<Material::Type>
    struct MaterialTypeTraits;

    struct MaterialIDGroupCPUGPU
    {
        UINT standardIndex = kInvalid;
        UINT gridLineIndex = kInvalid;

    };
    static_assert
    (
        sizeof(MaterialIDGroupCPUGPU) == sizeof(UINT) * kNumParamExists,
        "MaterialIDGroupCPUGPU is incomplete"
    );

    struct MaterialArrBufferSrvIndexGroupCPUGPU
    {
        SRVHeapIndex standardSrv = kInvalid;
        SRVHeapIndex gridLineSrv = kInvalid;
    };

    static_assert
    (
        sizeof(MaterialArrBufferSrvIndexGroupCPUGPU) == sizeof(SRVHeapIndex) * kNumParamExists,
        "MaterialArrBufferSrvIndexGroupCPUGPU is incomplete"
    );

	struct GridLineCPUGPU
	{
        Vector4<float> gridColor;
        Vector4<float> backgroundColor;
        float gridScale = 1.0f;
        float gridRatio = 1.0f;
	};

    struct StandardCPU
    {
        std::string albedoTexture = "";
        std::string normalTexture = "";
        std::string emissiveTexture = "";
        Vector4<float> baseColor = { float(kInvalid),float(kInvalid),float(kInvalid),float(kInvalid) };
        float roughness = float(kInvalid);
        float metallic = float(kInvalid);
        StaticSampler::SamplerState albedoTexSamplerState = StaticSampler::SamplerState::kLinearClamp;
    };

    struct StandardGPU
    {
        SRVHeapIndex albedoTexture = kInvalid;
        SRVHeapIndex normalTexture = kInvalid;
        SRVHeapIndex emissiveTexture = kInvalid;
        Vector4<float> baseColor = { float(kInvalid),float(kInvalid),float(kInvalid),float(kInvalid) };
        float roughness = float(kInvalid);
        float metallic = float(kInvalid);
        StaticSampler::SamplerState albedoTexSamplerState = StaticSampler::SamplerState::kLinearClamp;

    };

}

template<>
struct Material::MaterialTypeTraits<Material::Type::kStandard>
{
    static constexpr UINT kReserveSize = 10;
    static inline const std::string kName = "Standard";
    using dataType = Material::StandardGPU;
};

template<>
struct Material::MaterialTypeTraits<Material::Type::kGridLine>
{
    static constexpr UINT kReserveSize = 10;
    static inline const std::string kName = "GridLine";
    using dataType = Material::GridLineCPUGPU;
};


#else

struct MaterialGridLine
{
    float4 gridColor;
    float4 backgroundColor;
    float gridScale;
    float gridRatio;
};

struct MaterialStandard
{
    uint albedoIndex;
    uint normalIndex;
    uint emissiveIndex;
    float4 baseColor;
    float roughness;
    float metallic;
    uint samplerState;
};


struct MaterialIDGroup
{
    uint standardIndex;
    uint gridLineIndex;
};

struct MaterialArrBufferSrvIndexGroup
{
    uint standardSrv;
    uint gridLineSrv;
};


#endif
