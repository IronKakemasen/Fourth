struct VertexOut
{
    float4 Position : SV_Position;
    float4 Color :TEXCOORD0;
};


[NumThreads(3, 1, 1)]
[OutputTopology("triangle")]
void main
(
    uint gtid : SV_GroupThreadID, 
    uint groupID_ : SV_GroupID,
    out vertices VertexOut verts[3], 
    out indices uint3 tris[1] 
)
{
    SetMeshOutputCounts(3, 1);

    float3 positions[3] =
    {
        float3(0.0f, 0.5f, 0.0f), 
        float3(0.5f, -0.5f, 0.0f), 
        float3(-0.5f, -0.5f, 0.0f) 
    };

    float4 colors[3] =
    {
        float4(1.0f, 0.0f, 0.0f, 1.0f), 
        float4(0.0f, 1.0f, 0.0f, 1.0f), 
        float4(0.0f, 0.0f, 1.0f, 1.0f) 
    };


    verts[gtid].Position = float4(positions[gtid], 1.0f);
    verts[gtid].Color = colors[gtid];

    if (gtid == 0)
    {
        tris[0] = uint3(0, 1, 2);
    }
}