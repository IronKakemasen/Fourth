#include "PreCompileHeader.h"
#include "ResourceAssembler.h"
#include "../../../ResourceCreator/ResourceCreator.h"
#include "../../../../BufferDefinition/AllBufferDescsInclude.h"

namespace
{
    auto const fileName = "ResourceAssembler.cpp";
}



BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::ResourceAssembler::CreateResource
(
    const BufferContext::ResourceCreator& resourceCreator_,
    std::optional<D3D12_CLEAR_VALUE> cleaValue_,
    const std::string& nameCnv_,
    const BufferDescriptionBehavior& desc_
)
{

    //リソースディスクとヒーププロパティを取得
    std::pair < D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES > resDesc_Props = CreateRequirements(desc_);

    //リソース生成
    return resourceCreator_.Create
    (
        resDesc_Props.first,
        resDesc_Props.second,
        cleaValue_.has_value() ? &(*cleaValue_) : nullptr,
        desc_.initialState,
        nameCnv_,
        (UINT)desc_.numBuffer
    );

}

std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> BufferContext::BufferAssembler::ResourceAssembler::CreateRequirements(const BufferDescriptionBehavior& desc_)
{
    //要項チェック
    desc_.CheckRequirementsFilled();
    Logger::Log("Check: RequirementsFilled", fileName);

    D3D12_HEAP_PROPERTIES heapProp = desc_.CreateHeapProperties();

    D3D12_RESOURCE_DESC resourceDesc = desc_.CreateResourceDesc();

    return std::make_pair(resourceDesc, heapProp);

}


template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const ColorBufferDescription& desc_)
{
    return desc_.WatchClearValue();
}

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const DepthStencilBufferDescription& desc_)
{
    return desc_.WatchClearValue();
}

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const ConstantBufferDescription& desc_)
{
    return std::nullopt;
}

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const StaticStructuredBufferDescription& desc_)
{
    return std::nullopt;
}

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const UploadStructuredBufferDescription& desc_)
{
    return std::nullopt;
}

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const ComputeBufferDescription& desc_)
{
    return std::nullopt;
}


