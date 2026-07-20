#pragma once
#include "../../BufferContext.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

//バッファクラスの前方宣言
#include "../../BufferDefinition/AllBuffersFwd.h"
#include "../../BufferDefinition/AllBufferDescsInclude.h"

//リソース生成
#include "../ResourceCreator/ResourceCreator.h"

//外部
#include "../../../../Core/DescriptorHeap/DescriptorHeapContext.h"


//ビュー生成ツール
class DescriptorHeapContext::ViewCreator;



//バッファとディスクを特定のクラスに限定して組み立てる
class BufferContext::BufferAssembler
{
    using ResourceContainer = std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>;

    //ツール
    BufferContext::ResourceCreator* resourceCreator;
    DescriptorHeapContext::ViewCreator* viewCreator;

public:

    BufferAssembler
    (
        BufferContext::InstanceKey instancekey_, 
        ResourceCreator* resourceCreator_,
        DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_
    );

    ///☆☆☆バッファ生成関数（本丸）☆☆☆
    template<typename BufferType, typename DescType>
    [[nodiscard]] std::unique_ptr<BufferType> Assemble(const DescType& desc_, const std::string& name_)
    {
        //名前変換
        std::string nameCnv = ConvertName<BufferType>(name_);

        Logger::Entry("AssemblingStart:" + nameCnv);

        //リソース生成に必要な情報を組み立てる
        std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> resourceDescAndHeapProp  = AssembleResourceCreateRequirements(desc_);


        //生リソース生成
        ResourceContainer resourceContainer =
            std::move(AssembleResource(resourceDescAndHeapProp.first, resourceDescAndHeapProp.second, nameCnv, desc_));

        //バッファの実体生成
        std::unique_ptr<BufferType> buffer = std::move
        (
            AssembleBuffer<BufferType>(std::move(resourceContainer), desc_, nameCnv)
        );

        //ビュー生成。ConstantBuffer以外
        if constexpr (!std::is_same_v<BufferType, ConstantBuffer>)
        {
            GPUBufferBehavior::ResourceAccessKey reourceAccessKey;
            GPUBufferBehavior::InstanceKey instanceKey;

            AssembleView<BufferType>(buffer.get(), desc_, reourceAccessKey, instanceKey);
        }

        Logger::End("AssemblingComplete:" + nameCnv);

        return buffer;
    }


private:

    //生リソース生成
    template<typename DescType>
    ResourceContainer AssembleResource
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
            desc_.initialState,
            nameCnv_,
            (UINT)desc_.numBuffer

        );
    }
   
    //名前変換
    template<typename BufferType>
    std::string ConvertName(const std::string& srcName_)
    {
        std::string attach;

        if constexpr (std::is_same_v<BufferType, ConstantBuffer>)               attach  = "Constant";
        else if constexpr (std::is_same_v<BufferType, ColorBuffer>)             attach  = "Color";
        else if constexpr (std::is_same_v<BufferType, DepthStencilBuffer>)      attach  = "DepthStencil";
        else if constexpr (std::is_same_v<BufferType, ComputeBuffer>)           attach  = "Compute";
        else if constexpr (std::is_same_v<BufferType, UploadStructuredBuffer>)  attach  = "UploadStructured";
        else if constexpr (std::is_same_v<BufferType, StaticStructuredBuffer>)  attach  = "StaticStructuredBuffer";

        return attach + "Buffer" + "[ " + srcName_ + " ] ";
    }

    //クリアバリュー取得
    template<typename DescType>
    std::optional<D3D12_CLEAR_VALUE> GetClearValue(const DescType& desc_);

    //バッファ生成
    template<typename BufferType, typename DescType>
    std::unique_ptr<BufferType> AssembleBuffer(ResourceContainer resourceContainer_, const DescType& desc_, std::string nameCnv_);
    
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
(ResourceContainer resourceContainer_, const ColorBufferDescription& desc_, std::string nameCnv_);

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
(ResourceContainer resourceContainer_, const DepthStencilBufferDescription& desc_, std::string nameCnv_);

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ConstantBufferDescription& desc_);

template<>
std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::AssembleBuffer<ConstantBuffer, ConstantBufferDescription>
(ResourceContainer resourceContainer_, const ConstantBufferDescription& desc_, std::string nameCnv_);

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
(ResourceContainer resourceContainer_, const ComputeBufferDescription& desc_, std::string nameCnv_);
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const StaticStructuredBufferDescription& desc_);

template<>
void BufferContext::BufferAssembler::AssembleView<StaticStructuredBuffer, StaticStructuredBufferDescription>
(StaticStructuredBuffer* buffer_, const StaticStructuredBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_);

template<>
std::unique_ptr<StaticStructuredBuffer> BufferContext::BufferAssembler::AssembleBuffer<StaticStructuredBuffer, StaticStructuredBufferDescription>
(ResourceContainer resourceContainer_, const StaticStructuredBufferDescription& desc_, std::string nameCnv_);
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const UploadStructuredBufferDescription& desc_);

template<>
void BufferContext::BufferAssembler::AssembleView<UploadStructuredBuffer, UploadStructuredBufferDescription>
(UploadStructuredBuffer* buffer_, const UploadStructuredBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_);

template<>
std::unique_ptr<UploadStructuredBuffer> BufferContext::BufferAssembler::AssembleBuffer<UploadStructuredBuffer, UploadStructuredBufferDescription>
(ResourceContainer resourceContainer_, const UploadStructuredBufferDescription& desc_, std::string nameCnv_);
