#include "PreCompileHedder.h"
#include "BufferAssembler.h"

//バッファ
#include "../GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"
#include "../GPUBuffer/SRV_UAVBuffer/SRV_UAVBuffer.h"

//ディスクリプション
#include "../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"
#include "../BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"
#include "../BufferDescriptions/SRV_UAVBufferDescription/SRV_UAVBufferDescription.h"

//ツール
#include "../ResourceCreator/ResourceCreator.h"
#include "../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"

BufferAssembler::BufferAssembler(ResourceCreator* resourceCreator_, ViewCreator* viewCreator_)
	:resourceCreator(resourceCreator_), viewCreator(viewCreator_)
{

}

std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> BufferAssembler::AssembleResourceCreateRequirements(const IBufferDescription& desc_)
{
	D3D12_HEAP_PROPERTIES heapProp = desc_.CreateHeapProperties();
	D3D12_RESOURCE_DESC resourceDesc = desc_.CreateResourceDesc();

	return std::make_pair(resourceDesc, heapProp);
}



template<>
std::unique_ptr<ColorBuffer> BufferAssembler::AssembleResource(D3D12_RESOURCE_DESC resourceDesc_, D3D12_HEAP_PROPERTIES heapProp_,const std::string& name_ ,ColorBufferDescription desc_)
{
	using DoubleResource = std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>> ;

	//名前変換
	std::string nameCnv = ConvertName(name_, "ColorBuffer");

	//クリアバリュー必要
	auto clearValue = desc_.WatchClearValue();
	//リソース生成
	DoubleResource doubleResource = resourceCreator->CreateResource(resourceDesc_, heapProp_, &clearValue, nameCnv);

	//移し替え
	auto descPtr = std::make_unique<ColorBufferDescription>(std::move(desc_));

	//バッファ生成
	return std::make_unique<ColorBuffer>
	(
		ColorBuffer::InstanceKey{},
		nameCnv,
		std::move(doubleResource.first), std::move(doubleResource.second),
		std::move(descPtr)
	);
}

template<>
void BufferAssembler::AssembleView(ColorBuffer* buffer_, const ColorBufferDescription& desc_)
{
	auto srv = desc_.CreateSRV_Desc();
	auto rtv = desc_.CreateRTV_Desc();

	for (int i = 0;i < ProjectConfig::Render::kRequiredGPUBufferSum;++i)
	{
		auto accessKey = ColorBuffer::BufferAccessKey{};
		auto instanceKey = ColorBuffer::InstanceKey{};

		//srvを作り、インデックスを格納
		uint32_t srvHeapIndex = viewCreator->CreateView<uint32_t>(buffer_->GetResource(accessKey , i), srv);
		buffer_->OverrideIndex<ViewType::kSRV>(instanceKey, srvHeapIndex, i);

		//rtvを作り、インデックスを格納
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapIndex = viewCreator->CreateView<D3D12_CPU_DESCRIPTOR_HANDLE>(buffer_->GetResource(accessKey , i), rtv);
		buffer_->OverrideIndex<ViewType::kRTV>(instanceKey, rtvHeapIndex, i);

	}
}



std::string BufferAssembler::ConvertName(const std::string& srcName_, const std::string& attach_)
{
	return attach_ + "[ " + srcName_ + " ] ";
}


