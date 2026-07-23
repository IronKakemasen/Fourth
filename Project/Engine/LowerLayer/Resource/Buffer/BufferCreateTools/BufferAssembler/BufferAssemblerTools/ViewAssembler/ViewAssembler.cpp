#include "PreCompileHeader.h"
#include "ViewAssembler.h"
#include "../../../../BufferDefinition/AllBufferDescsInclude.h"

//外部
#include "../../../../../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"


namespace
{
    auto const fileName = "ViewAssembler.cpp";
}


template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const ColorBufferDescription& desc_
)
{
    auto srvDesc = desc_.CreateSRV_Desc();
    auto rtvDesc = desc_.CreateRTV_Desc();

    for (int i = 0;i < (int)desc_.numBuffer;++i)
    {
        //srv作成
        CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, srvDesc, i);
        Logger::Log("Create: srv", fileName);
        //rtv生成
        CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, rtvDesc, i);
        Logger::Log("Create: rtv", fileName);

    }
}

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const DepthStencilBufferDescription& desc_
)
{
    auto srvDesc = desc_.CreateSRV_Desc();
    auto dsvDesc = desc_.CreateDSVDesc();

    for (int i = 0;i < (int)desc_.numBuffer;++i)
    {
        //srv作成
        CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, srvDesc, i);
        Logger::Log("Create: srv", fileName);
        //DSV生成
        CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, dsvDesc, i);
        Logger::Log("Create: dsv", fileName);

    }

}

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const ComputeBufferDescription& desc_
)
{
    auto srvDesc = desc_.CreateSRV_Desc();
    auto uavDesc = desc_.CreateUAV_Desc();

    for (int i = 0;i < (int)desc_.numBuffer;++i)
    {
        //srv作成
        CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, srvDesc, i);
        Logger::Log("Create: srv", fileName);
        //UAV生成
        CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, uavDesc, i);
        Logger::Log("Create: uav", fileName);
    }

}

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const StaticStructuredBufferDescription& desc_
)
{
    auto srvDesc = desc_.CreateSRV_Desc();

    //srv作成
    CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, srvDesc, 0);
    Logger::Log("Create: srv", fileName);

}

template<>
void BufferContext::BufferAssembler::ViewAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const UploadStructuredBufferDescription& desc_
)
{
    auto srvDesc = desc_.CreateSRV_Desc();

    //srv作成
    CreateView(accessKey_, instanceKey_, viewCreator_,buffer_, srvDesc, 0);
    Logger::Log("Create: srv", fileName);
    //srv生成
    CreateView(accessKey_, instanceKey_, viewCreator_, buffer_, srvDesc, 1);
    Logger::Log("Create: srv", fileName);
}



template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_RENDER_TARGET_VIEW_DESC& viewDescType_,
    uint8_t index_
)
{
    D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

    std::tie(std::ignore, rtvCPU, std::ignore) = viewCreator_.CreateView(buffer_->GetResource(accessKey_, index_), &viewDescType_);
    buffer_->OverrideHeapIndex<ViewType::kRTV>(instanceKey_, rtvCPU, index_);

}

template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_DEPTH_STENCIL_VIEW_DESC& viewDescType_,
    uint8_t index_
)
{
    D3D12_CPU_DESCRIPTOR_HANDLE dsvCPU{};

    std::tie(std::ignore, dsvCPU, std::ignore) = viewCreator_.CreateView(buffer_->GetResource(accessKey_, index_), &viewDescType_);
    buffer_->OverrideHeapIndex<ViewType::kDSV>(instanceKey_, dsvCPU, index_);

}

template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_SHADER_RESOURCE_VIEW_DESC& viewDescType_,
    uint8_t index_
)
{
    SRVHeapIndex srvIndex{};
    D3D12_CPU_DESCRIPTOR_HANDLE srvCPU{};
    D3D12_GPU_DESCRIPTOR_HANDLE srvGPU{};

    std::tie(srvIndex, srvCPU, srvGPU) = viewCreator_.CreateView(buffer_->GetResource(accessKey_, index_), &viewDescType_);
    buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey_, srvIndex, index_);
    buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey_, srvCPU, index_);
    buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey_, srvGPU, index_);

}

template<>
void BufferContext::BufferAssembler::ViewAssembler::CreateView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    DescriptorHeapContext::ViewCreator& viewCreator_,
    GPUBufferBehavior* buffer_,
    const D3D12_UNORDERED_ACCESS_VIEW_DESC& viewDescType_,
    uint8_t index_
)
{
    SRVHeapIndex uavIndex{};
    D3D12_CPU_DESCRIPTOR_HANDLE uavCPU{};
    D3D12_GPU_DESCRIPTOR_HANDLE uavGPU{};

    std::tie(uavIndex, uavCPU, uavGPU) = viewCreator_.CreateView(buffer_->GetResource(accessKey_, index_), &viewDescType_);
    buffer_->OverrideHeapIndex<ViewType::kUAV>(instanceKey_, uavIndex, index_);
    buffer_->OverrideHeapIndex<ViewType::kUAV>(instanceKey_, uavCPU, index_);
    buffer_->OverrideHeapIndex<ViewType::kUAV>(instanceKey_, uavGPU, index_);

}
