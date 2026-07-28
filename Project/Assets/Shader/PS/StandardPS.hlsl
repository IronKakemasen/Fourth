SamplerState samp : register(s0);

struct MeshShaderOutput
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : POSITION0;
};

struct PixelShaderOutput
{
    float4 color : SV_Target0;
};

PixelShaderOutput main(MeshShaderOutput input_)
{
    PixelShaderOutput output;
    
    output.color = float4(1,1,0.5,1);
    return output;
}