#pragma once

#ifdef __cplusplus

#include "../../Engine/Math/Vector/Vector4.h"

namespace ShaderParam
{
    enum class Type
    {
        kGridLine,



        kCount
    };

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


    using ParamUniques = std::tuple
    <
        std::unique_ptr<GridLineCPUGPU>
    >;
}

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
