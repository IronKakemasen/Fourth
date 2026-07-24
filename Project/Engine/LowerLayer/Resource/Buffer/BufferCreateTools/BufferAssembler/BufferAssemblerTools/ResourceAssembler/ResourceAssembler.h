#pragma once
#include "../../BufferAssembler.h"


class BufferContext::BufferAssembler::ResourceAssembler
{
    friend class BufferContext::BufferAssembler;

    //生リソース生成
    template<typename DescType>
    [[nodiscard]]static ResourceContainer AssembleResource
    (
        const BufferContext::ResourceCreator& resourceCreator_,
        const std::string& nameCnv_,
        const DescType& desc_
    )
    {
        std::optional<D3D12_CLEAR_VALUE> cleavalue = GetClearValue(desc_);

        return CreateResource
        (
            resourceCreator_,
            cleavalue,
            nameCnv_,
            desc_
        );
    }

    //生リソース生成に必要な情報を組み立てる
    static std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> CreateRequirements(const BufferDescriptionBehavior& desc_);


    //生リソース生成
    static ResourceContainer CreateResource
    (
        const BufferContext::ResourceCreator& resourceCreator_,
        std::optional<D3D12_CLEAR_VALUE> cleaValue_,
        const std::string& nameCnv_,
        const BufferDescriptionBehavior& desc_
    );

    //クリアバリュー取得
    //カラーバッファとディプスステンシルバッファのみ実体が存在
    template<typename DescType>
    static std::optional<D3D12_CLEAR_VALUE> GetClearValue(const DescType& desc_);

};


template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const ColorBufferDescription& desc_);

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const DepthStencilBufferDescription& desc_);

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const ConstantBufferDescription& desc_);

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const StaticStructuredBufferDescription& desc_);

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const UploadStructuredBufferDescription& desc_);

template<>
std::optional<D3D12_CLEAR_VALUE>
BufferContext::BufferAssembler::ResourceAssembler::GetClearValue(const ComputeBufferDescription& desc_);
