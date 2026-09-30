#include "../../../Shared/StructuredBufferModelData.h"
#include "../../../Shared/ConstantBuffers.h"


struct MSOutput
{
    float4 position : SV_Position;
    float2 uv       : TEXCOORD0;
};

[outputtopology("triangle")]
[numthreads(3, 1, 1)]
void main
(
    uint groupThreadID_ : SV_GroupThreadID,
    out vertices MSOutput verts_[3],
    out indices uint3 polys_[1]
)
{
    SetMeshOutputCounts(3, 1);

    if (groupThreadID_ < 3)
    {
        float2 uv = float2((groupThreadID_ << 1) & 2, groupThreadID_ & 2);

        verts_[groupThreadID_].position = float4(uv * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
        verts_[groupThreadID_].uv = uv;
    }

    if (groupThreadID_ == 0)
    {
        polys_[0] = uint3(0, 1, 2);
    }
}
