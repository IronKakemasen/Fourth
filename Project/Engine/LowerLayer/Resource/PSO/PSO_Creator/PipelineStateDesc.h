#pragma once
#include "../../../Render/RenderStateComponent.h"
#include "../../../Render/RenderPass/RenderPassComponent.h"
#include "../../../../External/d3dx12/d3dx12.h"

namespace PipelineStateComponent
{
    struct ShaderSet
    {
        IDxcBlob* meshShader;
        IDxcBlob* pixelShader;
        std::string meshShaderName;
        std::string pixelShaderName;

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
        std::vector<DXGI_FORMAT> rtvFormatContainer;
        std::vector<RenderStateComponent::BlendMode> blendModeContainer;
        std::vector<std::string> bufferNameContainer;

    };

    struct DepthStencilDesc
    {
        DXGI_FORMAT dsvFormat;
        RenderStateComponent::BlendMode blendMode = RenderStateComponent::BlendMode::kOpaque;
        RenderPassComponent::DepthEnable depthEnable = RenderPassComponent::DepthEnable::kEnable;
        RenderPassComponent::DepthTest depthTest = RenderPassComponent::DepthTest::kGreaterEqual;
        float clearDepth = 0.0f;
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
        PipelineStateComponent::ShaderSet shaderSet;
        PipelineStateComponent::RasterizerDesc rasterizerDesc;
        PipelineStateComponent::RenderTargetDesc renderTargetDesc;
        std::optional<PipelineStateComponent::DepthStencilDesc> depthStencilDesc;
        PipelineStateComponent::SampleDesc sampleDesc;
    };


}

