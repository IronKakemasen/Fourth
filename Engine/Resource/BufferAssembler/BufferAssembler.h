#pragma once
#include"../BufferDescriptions/BufferDescriptionBehavior.h"
#include "../BufferContext.h"

//ツール
class ViewCreator;

//ディスクリプション
struct ColorBufferDescription;
struct ConstantBufferDescription;
struct DepthStencilBufferDescription;
struct SRV_UAVBufferDescription;

//バッファ
class ColorBuffer;
class ConstantBuffer;
class DepthStencilBuffer;
class SRV_UAVBuffer;


//バッファとディスクを特定のクラスに限定して組み立てる
class BufferContext::BufferAssembler
{
public:
    BufferAssembler
    (
        BufferContext::InstanceKey instancekey_, 
        std::unique_ptr<BufferContext::ResourceCreator> resourceCreator_, 
        ViewCreator* viewCreator_
    );

    template<typename BufferType, typename DescType>
    [[nodiscard]] std::unique_ptr<BufferType> Assemble(const DescType& desc_, const std::string& name_)
    {
        //リソース生成に必要な情報を組み立てる
        std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> resourceDescAndHeapProp  = AssembleResourceCreateRequirements(desc_);

        //実体生成、リソースも生成
        std::unique_ptr<BufferType> buffer = std::move
        (
            AssembleResource<BufferType>(resourceDescAndHeapProp.first, resourceDescAndHeapProp.second, name_, desc_)
        );

        //ビュー生成。ConstantBuffer以外
        if constexpr (!std::is_same_v<BufferType, ConstantBuffer>)
        {
            AssembleView<BufferType>(buffer.get(), desc_);
        }

        return buffer;
    }


private:

    //バッファ生成、中身のリソースも生成
    template<typename BufferType, typename DescType>
    std::unique_ptr<BufferType> AssembleResource
    (
        D3D12_RESOURCE_DESC resourceDesc_,
        D3D12_HEAP_PROPERTIES heapProp_,
        const std::string& name_,
        const DescType& desc_
    );
    
    //ビュー生成
    template<typename BufferType, typename DescType>
    void AssembleView(BufferType* buffer_ , const DescType& desc_);

    //リソース生成に必要なものを組み立てる
    std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> AssembleResourceCreateRequirements(const BufferDescriptionBehavior& desc_);

    //名前変換
    std::string ConvertName(const std::string& srcName_, const std::string& attach_);

    std::unique_ptr<BufferContext::ResourceCreator> resourceCreator;
    ViewCreator* viewCreator;
};


template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::AssembleResource<ColorBuffer, ColorBufferDescription>
(
    D3D12_RESOURCE_DESC resourceDesc_,
    D3D12_HEAP_PROPERTIES heapProp_, 
    const std::string& name_,
    const ColorBufferDescription& desc_
);

template<>
void BufferContext::BufferAssembler::AssembleView<ColorBuffer, ColorBufferDescription>
    (ColorBuffer* buffer_, const ColorBufferDescription& desc_);



template<>
std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::AssembleResource<DepthStencilBuffer, DepthStencilBufferDescription>
(
    D3D12_RESOURCE_DESC resourceDesc_,
    D3D12_HEAP_PROPERTIES heapProp_,
    const std::string& name_,
    const DepthStencilBufferDescription& desc_
);

template<>
void BufferContext::BufferAssembler::AssembleView<DepthStencilBuffer, DepthStencilBufferDescription>
(DepthStencilBuffer* buffer_, const DepthStencilBufferDescription& desc_);
