#include "../../../Shared/ConstantBuffers.h"
#include "../../../Shared/StaticSampler.h"


struct PSInput
{
    float4 position : SV_Position;
    float2 uv       : TEXCOORD0;
};

float4 main(PSInput input_) : SV_Target
{
    //パスが参照するバッファのsrvHeapIndexの配列
    StructuredBuffer<uint> refBufferSrvIndices = ResourceDescriptorHeap[gPassRefBufferContainerIndex];

    Texture2D<float4> sceneOpaque = ResourceDescriptorHeap[refBufferSrvIndices[gPassConstants.refBufferOffset]];
    
    return sceneOpaque.Sample(sampler_linearWrap, input_.uv);
}
