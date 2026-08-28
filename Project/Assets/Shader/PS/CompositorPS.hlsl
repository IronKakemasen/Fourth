#include "../../Shared/ConstantBuffers.h"
#include "../../Shared/StructuredBuffer.h"
#include "../../Shared/StaticSampler.h"


struct PSInput
{
    float4 position : SV_Position;
    float2 uv       : TEXCOORD0;
};

float4 main(PSInput input_) : SV_Target
{
    // 簡易版：offsetを直接シーンカラーのSRVHeapIndexとして解釈する
    Texture2D<float4> sceneColor = ResourceDescriptorHeap[gPassBufferIndexRange.offset];

    return sceneColor.Sample(sampler_linearWrap, input_.uv);
}
