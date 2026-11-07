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

    struct ShaderParamArrSrvIndexGroupCPUGPU
    {
        SRVHeapIndex gridLineSrv = kInvalid;
    };

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

struct ShaderParamSrvIndexGrou
{
    uint gridLineSrv;
};


#endif
