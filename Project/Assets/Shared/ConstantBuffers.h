#pragma once
#include "../../Engine/MiddleLayer/Math/Vector/Vector4.h"

#ifdef __cplusplus

constexpr int kNumConstantBufferTypes = 1;

struct SceneCB
{
    //経過時間
    Vector4<float> passedTime;
};


#else

struct SceneCB
{
    float passedTime;
};

#endif