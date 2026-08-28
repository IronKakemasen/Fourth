#include "../../Shared/StructuredBuffer.h"
#include "../../Shared/ConstantBuffers.h"


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

    // groupThreadID_(0,1,2)だけから、画面全体を覆う三角形の3頂点を導出する。
    // uv: (0,0) (2,0) (0,2) という、画面外まではみ出す座標をわざと作り、
    // ラスタライズ時にちょうど画面全体がカバーされるようにする。
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
