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

    struct MaterialContainerIndicesCPUGPU
    {
        UINT standardIndex = kInvalid;
        UINT gridLineIndex = kInvalid;

    };
    static_assert
    (
        sizeof(MaterialContainerIndicesCPUGPU) == sizeof(UINT) * kNumParamExists,
        "MaterialContainerIndicesCPUGPUのデータサイズがおかしい"
    );

    struct MaterialArrSrvIndexGroupCPUGPU
    {
        SRVHeapIndex standardSrv = kInvalid;
        SRVHeapIndex gridLineSrv = kInvalid;
    };

    static_assert
    (
        sizeof(MaterialArrSrvIndexGroupCPUGPU) == sizeof(SRVHeapIndex) * kNumParamExists,
        "MaterialArrSrvIndexGroupCPUGPUのデータサイズがおかしい"
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

struct GridLine
{
    float4 gridColor;
    float4 backgroundColor;
    float gridScale;
    float gridRatio;
};

struct MaterialContainerIndices
{
    uint standardIndex;
    uint gridLineIndex;
};

struct MaterialArrSrvIndexGroup
{
    uint standardSrv;
    uint gridLineSrv;
};


#endif
