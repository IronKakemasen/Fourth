#pragma once


namespace RootSignatureLayoutComponent
{
    enum class ShaderStage
    {
        kAll,  
        kVS,   
        kHS,   
        kDS,   
        kGS,   
        kPS,
        kAS,
        kMS
    };


    enum class Usage
    {
        kGraphics,
        kCompute
    };

    inline D3D12_SHADER_VISIBILITY Convert(ShaderStage stage_)
    {
        D3D12_SHADER_VISIBILITY cnv = D3D12_SHADER_VISIBILITY_ALL;

        switch (stage_)
        {
        case RootSignatureLayoutComponent::ShaderStage::kAll:
            cnv = D3D12_SHADER_VISIBILITY_ALL;
            break;
        case RootSignatureLayoutComponent::ShaderStage::kVS:
            cnv = D3D12_SHADER_VISIBILITY_VERTEX;

            break;
        case RootSignatureLayoutComponent::ShaderStage::kHS:
            cnv = D3D12_SHADER_VISIBILITY_HULL;

            break;
        case RootSignatureLayoutComponent::ShaderStage::kDS:
            cnv = D3D12_SHADER_VISIBILITY_DOMAIN;

            break;
        case RootSignatureLayoutComponent::ShaderStage::kGS:
            cnv = D3D12_SHADER_VISIBILITY_GEOMETRY;

            break;
        case RootSignatureLayoutComponent::ShaderStage::kPS:
            cnv = D3D12_SHADER_VISIBILITY_PIXEL;

            break;
        case RootSignatureLayoutComponent::ShaderStage::kAS:
            cnv = D3D12_SHADER_VISIBILITY_AMPLIFICATION;

            break;
        case RootSignatureLayoutComponent::ShaderStage::kMS:
            cnv = D3D12_SHADER_VISIBILITY_MESH;
            break;

        default:

            ErrorMessageOutput::Assert::DetectError(false, "ShaderStageに想定外な値","RootSignatureLayoutComponent.h");
            break;
        }

        return cnv;
    }

}