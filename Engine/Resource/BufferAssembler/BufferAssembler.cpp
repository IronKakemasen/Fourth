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

BufferContext::BufferAssembler::BufferAssembler
(
	BufferContext::InstanceKey instancekey_, 
	std::unique_ptr<BufferContext::ResourceCreator> resourceCreator_, 
	ViewCreator* viewCreator_
)
	:resourceCreator(std::move(resourceCreator_)), viewCreator(viewCreator_)
{

}

std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> BufferContext::BufferAssembler::AssembleResourceCreateRequirements(const BufferDescriptionBehavior& desc_)
{
	//要項チェック
	desc_.CheckRequirementsFilled();

	D3D12_HEAP_PROPERTIES heapProp = desc_.CreateHeapProperties();
	D3D12_RESOURCE_DESC resourceDesc = desc_.CreateResourceDesc();
	
	return std::make_pair(resourceDesc, heapProp);
}



template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::AssembleResource<ColorBuffer, ColorBufferDescription>
(
	D3D12_RESOURCE_DESC resourceDesc_,
	D3D12_HEAP_PROPERTIES heapProp_,
	const std::string& name_,
	const ColorBufferDescription& desc_
)
{
	using DoubleResource = std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>> ;
	
	//名前変換
	std::string nameCnv = ConvertName(name_, "ColorBuffer");

	//クリアバリュー必要
	auto clearValue = desc_.WatchClearValue();
	//リソース生成
	DoubleResource doubleResource = resourceCreator->Create(resourceDesc_, heapProp_, &clearValue, desc_.initialState,nameCnv);

	//バッファ生成
	return std::make_unique<ColorBuffer>
	(
		ColorBuffer::InstanceKey{},
		nameCnv,
		std::move(doubleResource.first), std::move(doubleResource.second),
		std::make_unique<ColorBufferDescription>(desc_)
	);
}

template<>
void BufferContext::BufferAssembler::AssembleView<ColorBuffer, ColorBufferDescription>(ColorBuffer* buffer_, const ColorBufferDescription& desc_)
{
	auto srvDesc = desc_.CreateSRV_Desc();
	auto rtvDesc = desc_.CreateRTV_Desc();

	for (int i = 0;i < ProjectConfig::Render::kRequiredGPUBufferSum;++i)
	{
		auto accessKey = ColorBuffer::BufferAccessKey{};
		auto instanceKey = ColorBuffer::InstanceKey{};

		//srv生成
		{
			uint32_t srvIndex{};
			D3D12_CPU_DESCRIPTOR_HANDLE srvCPU{};
			D3D12_GPU_DESCRIPTOR_HANDLE srvGPU{};

			std::tie(srvIndex, srvCPU, srvGPU) = viewCreator->CreateView(buffer_->GetResource(accessKey, i), srvDesc);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvIndex, i);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvCPU, i);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvGPU, i);
		}

		//rtv生成
		{
			D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

			std::tie(std::ignore, rtvCPU, std::ignore) = viewCreator->CreateView(buffer_->GetResource(accessKey, i), rtvDesc);
			buffer_->OverrideHeapIndex<ViewType::kRTV>(instanceKey, rtvCPU, i);
		}
	}
}

std::string BufferContext::BufferAssembler::ConvertName(const std::string& srcName_, const std::string& attach_)
{
	return attach_ + "[ " + srcName_ + " ] ";
}


