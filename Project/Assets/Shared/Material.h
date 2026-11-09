#pragma once

#ifdef __cplusplus

#include "../../Engine/Math/Vector/Vector4.h"

namespace Material
{
    enum class Type
    {
        //kStandard,
        kGridLine,



        kCount
    };

    template<Material::Type>
    struct MaterialTypeTraits;

    struct ShaderParamContinerIndicesCPUGPU
    {
        UINT gridLineIndex = kInvalid;

    };
    static_assert
    (
        sizeof(ShaderParamContinerIndicesCPUGPU) == sizeof(UINT) * size_t(Type::kCount),
        "ShaderParamContinerIndicesCPUGPUのデータサイズがおかしい"
    );

    struct ShaderParamArrSrvIndexGroupCPUGPU
    {
        SRVHeapIndex gridLineSrv = kInvalid;
    };

    static_assert
    (
        sizeof(ShaderParamArrSrvIndexGroupCPUGPU) == sizeof(SRVHeapIndex) * size_t(Type::kCount),
        "ShaderParamArrSrvIndexGroupCPUGPUのデータサイズがおかしい"
    );

	struct GridLineCPUGPU
	{
        Vector4<float> gridColor;
        Vector4<float> backgroundColor;
        float gridScale = 1.0f;
        float gridRatio = 1.0f;
	};

}

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

struct ShaderParamContainerIndices
{
    uint gridLineIndex;
};

struct ShaderParamArrSrvIndexGroup
{
    uint gridLineSrv;
};


#endif
