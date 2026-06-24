#pragma once
#include "../BufferContext.h"
#include "../GPUBuffer/GPUBufferBehavior.h"
//ツール
#include "../ResourceCreator/ResourceCreator.h"

//ツール
class ViewCreator;

//ディスクリプション
struct ColorBufferDescription;
struct ConstantBufferDescription;
struct DepthStencilBufferDescription;
struct ComputeBufferDescription;
struct UploadStructuredBufferDescription;

//バッファ
class ColorBuffer;
class ConstantBuffer;
class DepthStencilBuffer;
class ComputeBuffer;
class UploadStructuredBuffer;


//バッファとディスクを特定のクラスに限定して組み立てる
class BufferContext::BufferAssembler
{
    using DoubleResource = std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>>;

    //ツール
    std::unique_ptr<BufferContext::ResourceCreator> resourceCreator;
    ViewCreator* viewCreator;

public:

    BufferAssembler
    (
        BufferContext::InstanceKey instancekey_, 
        std::unique_ptr<BufferContext::ResourceCreator> resourceCreator_, 
        ViewCreator* viewCreator_
    );

    ///☆☆☆バッファ生成関数（本丸）☆☆☆
    template<typename BufferType, typename DescType>
    [[nodiscard]] std::unique_ptr<BufferType> Assemble(const DescType& desc_, const std::string& name_)
    {
        //リソース生成に必要な情報を組み立てる
        std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> resourceDescAndHeapProp  = AssembleResourceCreateRequirements(desc_);

        //名前変換
        std::string nameCnv = ConvertName<BufferType>(name_);

        //生リソース生成
        DoubleResource doubleResource =
            AssembleResource(resourceDescAndHeapProp.first, resourceDescAndHeapProp.second, nameCnv, desc_);

        //バッファの実体生成
        std::unique_ptr<BufferType> buffer = std::move
        (
            AssembleBuffer<BufferType>(doubleResource, desc_, nameCnv)
        );

        //ビュー生成。ConstantBuffer以外
        if constexpr (!std::is_same_v<BufferType, ConstantBuffer>)
        {
            GPUBufferBehavior::ResourceAccessKey reourceAccessKey;
            GPUBufferBehavior::InstanceKey instanceKey;

            AssembleView<BufferType>(buffer.get(), desc_, reourceAccessKey, instanceKey);
        }

        return buffer;
    }


private:

    //生リソース生成
    template<typename DescType>
    DoubleResource AssembleResource
    (
        D3D12_RESOURCE_DESC resourceDesc_,
        D3D12_HEAP_PROPERTIES heapProp_,
        const std::string& nameCnv_,
        const DescType& desc_
    )
    {
        //クリアバリュー
        std::optional<D3D12_CLEAR_VALUE> clearValueOpt = GetClearValue(desc_);

        //リソース生成
        return resourceCreator->Create
        (
            resourceDesc_,
            heapProp_,
            clearValueOpt ? &clearValueOpt.value() : nullptr,
            desc_.initialStates,
            nameCnv_
        );
    }
   
    //名前変換
    template<typename BufferType>
    std::string ConvertName(const std::string& srcName_)
    {
        std::string attach;
        if constexpr (std::is_same_v<BufferType, ConstantBuffer>)attach = "Constant";
        else if constexpr (std::is_same_v<BufferType, ColorBuffer>)attach = "Color";
        else if constexpr (std::is_same_v<BufferType, DepthStencilBuffer>)attach = "DepthStencil";
        else if constexpr (std::is_same_v<BufferType, ComputeBuffer>)attach = "Compute";
        else if constexpr (std::is_same_v<BufferType, UploadStructuredBuffer>)attach = "UploadStructured";
       
        return attach + "Buffer" + "[ " + srcName_ + " ] ";
    }

    //クリアバリュー取得
    template<typename DescType>
    std::optional<D3D12_CLEAR_VALUE> GetClearValue(const DescType& desc_);

    //バッファ生成
    template<typename BufferType, typename DescType>
    std::unique_ptr<BufferType> AssembleBuffer(DoubleResource doubleResource_, const DescType& desc_, std::string nameCnv_);
    
    //ビュー生成
    template<typename BufferType, typename DescType>
    void AssembleView
    (BufferType* buffer_, const DescType& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_);

    //生リソース生成に必要な情報を組み立てる
    std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> AssembleResourceCreateRequirements(const BufferDescriptionBehavior& desc_);

    //ビュー生成
    template<typename DescType>
    void CreateView
    (
        GPUBufferBehavior* buffer_,
        const DescType& desc_,
        uint8_t index_,
        GPUBufferBehavior::ResourceAccessKey accessKey_,
        GPUBufferBehavior::InstanceKey instanceKey_
    );
};


///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void BufferContext::BufferAssembler::CreateView
(
    GPUBufferBehavior* buffer_,
    const D3D12_RENDER_TARGET_VIEW_DESC& desc_,
    uint8_t index_,
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_
);

template<>
void BufferContext::BufferAssembler::CreateView
(
    GPUBufferBehavior* buffer_,
    const D3D12_DEPTH_STENCIL_VIEW_DESC& desc_,
    uint8_t index_,
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_
);

template<>
void BufferContext::BufferAssembler::CreateView
(
    GPUBufferBehavior* buffer_,
    const D3D12_SHADER_RESOURCE_VIEW_DESC& desc_,
    uint8_t index_,
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_
);

template<>
void BufferContext::BufferAssembler::CreateView
(
    GPUBufferBehavior* buffer_,
    const D3D12_UNORDERED_ACCESS_VIEW_DESC& desc_,
    uint8_t index_,
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_
);
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ColorBufferDescription& desc_);

template<>
void BufferContext::BufferAssembler::AssembleView<ColorBuffer, ColorBufferDescription>
(ColorBuffer* buffer_, const ColorBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_,GPUBufferBehavior::InstanceKey instanceKey_);

template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::AssembleBuffer<ColorBuffer, ColorBufferDescription>
(DoubleResource doubleResource_, const ColorBufferDescription& desc_, std::string nameCnv_);

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const DepthStencilBufferDescription& desc_);

template<>
void BufferContext::BufferAssembler::AssembleView<DepthStencilBuffer, DepthStencilBufferDescription>
(DepthStencilBuffer* buffer_, const DepthStencilBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_);

template<>
std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::AssembleBuffer<DepthStencilBuffer, DepthStencilBufferDescription>
(DoubleResource doubleResource_, const DepthStencilBufferDescription& desc_, std::string nameCnv_);

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ConstantBufferDescription& desc_);

template<>
std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::AssembleBuffer<ConstantBuffer, ConstantBufferDescription>
(DoubleResource doubleResource_, const ConstantBufferDescription& desc_, std::string nameCnv_);

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ComputeBufferDescription& desc_);

template<>
void BufferContext::BufferAssembler::AssembleView<ComputeBuffer, ComputeBufferDescription>
(ComputeBuffer* buffer_, const ComputeBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_);

template<>
std::unique_ptr<ComputeBuffer> BufferContext::BufferAssembler::AssembleBuffer<ComputeBuffer, ComputeBufferDescription>
(DoubleResource doubleResource_, const ComputeBufferDescription& desc_, std::string nameCnv_);

