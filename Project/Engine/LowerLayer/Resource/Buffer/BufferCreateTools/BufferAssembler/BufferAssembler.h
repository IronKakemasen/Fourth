#pragma once
#include "../../BufferContext.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

//バッファクラスの前方宣言
#include "../../BufferDefinition/AllBuffersFwd.h"
#include "../../BufferDefinition/AllBufferDescsIFwd.h"

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

        //生リソース生成
        ResourceContainer resourceContainer = std::move(AssembleResource(nameCnv, desc_));

        //バッファの実体生成
        std::unique_ptr<BufferType> buffer = std::move
        (
            Materialize<BufferType>(std::move(resourceContainer), desc_, nameCnv)
        );

        //ビュー生成。ConstantBuffer以外
        if constexpr (!std::is_same_v<BufferType, ConstantBuffer>)
        {
            GPUBufferBehavior::ResourceAccessKey reourceAccessKey;
            GPUBufferBehavior::InstanceKey instanceKey;

            AssembleView(reourceAccessKey, instanceKey,buffer.get(), desc_);
        }

        Logger::End("AssemblingComplete:" + nameCnv);

        return buffer;
    }


private:

    //生リソースを組み立てる
    class ResourceAssembler;
    //名前を変換する
    class BufferNameConverter;
    //バッファの実体を作る
    class BufferMaterializer;
    //viewCreatorを使ってバッファのビューを生成
    class ViewAssembler;

    //生リソース生成
    template<typename DescType>
    ResourceContainer AssembleResource
    (
        const std::string& nameCnv_,
        const DescType& desc_
    );

    //名前変換
    template<typename BufferType>
    std::string ConvertName(const std::string& srcName_);

    //バッファ生成
    template<typename BufferType>
    std::unique_ptr<BufferType> Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
    
    //ビュー生成
    template<typename DescType>
    void AssembleView
    (
        GPUBufferBehavior::ResourceAccessKey accessKey_, 
        GPUBufferBehavior::InstanceKey instanceKey_,
        GPUBufferBehavior* buffer_, 
        const DescType& desc_
    );

};



///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
    const std::string& nameCnv_,
    const ColorBufferDescription& desc_
);
template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
    const std::string& nameCnv_,
    const DepthStencilBufferDescription& desc_
);
template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
    const std::string& nameCnv_,
    const ConstantBufferDescription& desc_
);
template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
    const std::string& nameCnv_,
    const ComputeBufferDescription& desc_
);
template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
    const std::string& nameCnv_,
    const StaticStructuredBufferDescription& desc_
);
template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
    const std::string& nameCnv_,
    const UploadStructuredBufferDescription& desc_
);
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::string BufferContext::BufferAssembler::ConvertName<ColorBuffer>(const std::string& srcName_);
template<>
std::string BufferContext::BufferAssembler::ConvertName<DepthStencilBuffer>(const std::string& srcName_);
template<>
std::string BufferContext::BufferAssembler::ConvertName<ConstantBuffer>(const std::string& srcName_);
template<>
std::string BufferContext::BufferAssembler::ConvertName<StaticStructuredBuffer>(const std::string& srcName_);
template<>
std::string BufferContext::BufferAssembler::ConvertName<UploadStructuredBuffer>(const std::string& srcName_);
template<>
std::string BufferContext::BufferAssembler::ConvertName<ComputeBuffer>(const std::string& srcName_);
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
template<>
std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
template<>
std::unique_ptr<StaticStructuredBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
template<>
std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
template<>
std::unique_ptr<UploadStructuredBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
template<>
std::unique_ptr<ComputeBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_);
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void BufferContext::BufferAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    GPUBufferBehavior* buffer_,
    const ColorBufferDescription& desc_
);
template<>
void BufferContext::BufferAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    GPUBufferBehavior* buffer_,
    const DepthStencilBufferDescription& desc_
);
template<>
void BufferContext::BufferAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    GPUBufferBehavior* buffer_,
    const UploadStructuredBufferDescription& desc_
);
template<>
void BufferContext::BufferAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    GPUBufferBehavior* buffer_,
    const ComputeBufferDescription& desc_
);
template<>
void BufferContext::BufferAssembler::AssembleView
(
    GPUBufferBehavior::ResourceAccessKey accessKey_,
    GPUBufferBehavior::InstanceKey instanceKey_,
    GPUBufferBehavior* buffer_,
    const StaticStructuredBufferDescription& desc_
);
