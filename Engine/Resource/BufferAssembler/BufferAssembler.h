#pragma once

//ツール
class ResourceCreator;
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

struct IBufferDescription;

//バッファとディスクを特定のクラスに限定して組み立てる
class BufferAssembler
{
public:
    BufferAssembler(ResourceCreator* resourceCreator_, ViewCreator* viewCreator_);

    template<typename BufferType, typename DescriptionType>
    [[nodiscard]] std::unique_ptr<BufferType> Assemble(const DescriptionType& desc_, const std::string& name_)
    {
        //要項チェック
        desc_.CheckRequirementsFilled();

        //リソース生成に必要な情報を組み立てる
        std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> resourceDescAndHeapProp  = AssembleResourceCreateRequirements(desc_);

        //実体生成、リソースも生成
        std::unique_ptr<BufferType> buffer = std::move
        (
            AssembleResource<BufferType>(resourceDescAndHeapProp.first, resourceDescAndHeapProp.second, name_, desc_)
        );


        return buffer;
    }


private:

    //バッファ生成、中身のリソースも生成
    template<typename BufferType,typename DescriptionType>
    std::unique_ptr<BufferType> AssembleResource
    (
        D3D12_RESOURCE_DESC resourceDesc_,
        D3D12_HEAP_PROPERTIES heapProp_,
        const std::string& name_,
        DescriptionType desc_
    );
    
    //ビュー生成
    template<typename BufferType, typename DescriptionType>
    void AssembleView(BufferType* buffer_ , const DescriptionType& desc_);

    //リソース生成に必要なものを組み立てる
    std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> AssembleResourceCreateRequirements(const IBufferDescription& desc_);

    //名前変換
    std::string ConvertName(const std::string& srcName_, const std::string& attach_);


    ResourceCreator* resourceCreator;
    ViewCreator* viewCreator;
};


template<>
std::unique_ptr<ColorBuffer> BufferAssembler::AssembleResource
(
    D3D12_RESOURCE_DESC resourceDesc_,
    D3D12_HEAP_PROPERTIES heapProp_, 
    const std::string& name_,
    ColorBufferDescription desc_
);


template<>
void BufferAssembler::AssembleView(ColorBuffer* buffer_, const ColorBufferDescription& desc_);
