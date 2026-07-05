
#pragma once

#ifdef __cplusplus

constexpr int kNumConstantBufferTypes = 1;

struct SceneCB
{
    float passedTime;
    float pad0[3];
};

static_assert(sizeof(SceneCB) == 16);

#else

struct SceneCB
{
    float passedTime;
};

#endif