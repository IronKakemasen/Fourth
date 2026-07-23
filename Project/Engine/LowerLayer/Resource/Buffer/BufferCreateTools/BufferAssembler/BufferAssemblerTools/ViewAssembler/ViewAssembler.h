#pragma once
#include "../../BufferAssembler.h"

class BufferContext::BufferAssembler::ViewAssembler
{
public:

    friend class BufferContext::BufferAssembler;

    //ビュー生成
    template<typename DescType>
    static void AssembleView
    (
        GPUBufferBehavior::ResourceAccessKey accessKey_,
        GPUBufferBehavior::InstanceKey instanceKey_,
        DescriptorHeapContext::ViewCreator& viewCreator_,
        GPUBufferBehavior* buffer_,
        const DescType& desc_
    );

private:

    //ビュー生成ヘルパー
    template<typename ViewDescType>
    static void CreateView
    (
        GPUBufferBehavior::ResourceAccessKey accessKey_,
        GPUBufferBehavior::InstanceKey instanceKey_,
        DescriptorHeapContext::ViewCreator& viewCreator_,
        GPUBufferBehavior* buffer_,
        const ViewDescType& viewDescType_,
        uint8_t index_
    );

};


template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const ColorBufferDescription& desc_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const DepthStencilBufferDescription& desc_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const ComputeBufferDescription& desc_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const StaticStructuredBufferDescription& desc_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const UploadStructuredBufferDescription& desc_
);

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_RENDER_TARGET_VIEW_DESC& viewDescType_,
    uint8_t index_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_DEPTH_STENCIL_VIEW_DESC& viewDescType_,
    uint8_t index_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_SHADER_RESOURCE_VIEW_DESC& viewDescType_,
    uint8_t index_
);

template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_UNORDERED_ACCESS_VIEW_DESC& viewDescType_,
    uint8_t index_
);
