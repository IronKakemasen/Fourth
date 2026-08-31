#pragma once
#include "../../../Render/RenderStateComponent.h"
#include "../../../Render/RenderPass/RenderPassComponent.h"
#include "../../../../External/d3dx12/d3dx12.h"

namespace PipelineStateComponent
{
    struct ShaderSet
    {
        IDxcBlob* meshShader = nullptr;
        IDxcBlob* pixelShader = nullptr;
        std::string meshShaderName = "notSet";
        std::string pixelShaderName = "none";

    };

    struct RasterizerDesc
    {
        RenderStateComponent::CullMode cullMode;
        RenderStateComponent::FillMode fillMode;

        INT depthBias = D3D12_DEFAULT_DEPTH_BIAS;
        FLOAT depthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
        FLOAT slopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    };

    struct RenderTargetDesc
    {
        DXGI_FORMAT rtvFormat;
        RenderStateComponent::BlendMode blendMode;
        std::string bufferName;
    };

    struct DepthStencilDesc
    {
        //ちょっと対症療法的だが…
        bool doesUseBuffer = true;

        DXGI_FORMAT dsvFormat;
        RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kOpaque;
        RenderPassComponent::DepthEnable depthEnable = RenderPassComponent::DepthEnable::kEnable;
        RenderPassComponent::DepthTest depthTest = RenderPassComponent::DepthTest::kGreaterEqual;
        float clearDepth = 0.0f;
        int clearStencil = 0;
        std::string bufferName;
    };

    struct SampleDesc
    {
        ///一旦空
    };

    struct MeshShaderPipelineStateStreamDesc
    {
        CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;
        CD3DX12_PIPELINE_STATE_STREAM_MS MS;
        CD3DX12_PIPELINE_STATE_STREAM_PS PS;
        CD3DX12_PIPELINE_STATE_STREAM_RASTERIZER RasterizerState;
        CD3DX12_PIPELINE_STATE_STREAM_BLEND_DESC BlendState;
        CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL DepthStencilState;
        CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_DESC SampleDesc;
        CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_MASK SampleMask;
        CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;
        CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;
    };

}

namespace PipelineStateDesc
{
    struct Graphics
    {
        Graphics() = default;

        Graphics
        (
            PipelineStateComponent::ShaderSet const& shaderSet,
            PipelineStateComponent::RasterizerDesc const& rasterizerDesc,
            std::vector<PipelineStateComponent::RenderTargetDesc> const& renderTargetDescs,
            PipelineStateComponent::DepthStencilDesc const& depthStencilDesc,
            PipelineStateComponent::SampleDesc const& sampleDesc
        ):shaderSet(shaderSet),rasterizerDesc(rasterizerDesc),renderTargetDescs(renderTargetDescs),depthStencilDesc(depthStencilDesc),sampleDesc(sampleDesc)
        {
        }
        PipelineStateComponent::ShaderSet shaderSet;
        PipelineStateComponent::RasterizerDesc rasterizerDesc;
        std::vector<PipelineStateComponent::RenderTargetDesc> renderTargetDescs;
        PipelineStateComponent::DepthStencilDesc depthStencilDesc;
        PipelineStateComponent::SampleDesc sampleDesc;
    };
}

