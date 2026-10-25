#include "../../../Shared/StructuredBufferModelData.h"
#include "../../../Shared/StructuredBufferCameraData.h"
#include "../../../Shared/ConstantBuffers.h"
#include "../../../Shared/StaticSampler.h"


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


float3 DiffuseModelLambert(float3 normal_, float3 lightDir_, float3 diffuse_,
    float3 lightColor_, float intensity_)
{
    float cos = saturate(dot(normal_, -lightDir_));
    
    return lightColor_ * cos * diffuse_ * intensity_;
}

PixelShaderOutput main(MeshShaderOutput input_)
{
    PixelShaderOutput output;
    
    //カメラの実データ配列
    StructuredBuffer<CameraData> cameraDataContainer = ResourceDescriptorHeap[gCameraContainerIndex];
    //カメラの実データ配列からこのPassで使うものを指定する(数もどれかもPass依存)
    CameraData srcCameraData = cameraDataContainer[gPassConstants.cameraOffset];

    float3 dirLightDir = normalize(float3(0.0f,-0.5f,0.5f));
    float3 normal = normalize(input_.normal);
    float3 toCamera = normalize(srcCameraData.worldPos.xyz - input_.worldPosition);
    
    float3 diffuse = DiffuseModelLambert(normal, dirLightDir, 0.25f, float3(1.0f,1.0f,1.0f), 1.0f);
    
    output.color = float4(float3(1.0f, 1.0f, 1.0f) * diffuse, 1.0f);
    
    return output;
}
