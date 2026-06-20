#include "PreCompileHeader.h"
#include "BufferAssembler.h"

//バッファ
#include "../GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"
#include "../GPUBuffer/RWPingPongBuffer/RWPingPongBuffer.h"

//ディスクリプション
#include "../BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"
#include "../BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"
#include "../BufferDescriptions/RWPingPongBufferDescription/RWPingPongBufferDescription.h"

//ツール
#include "../ResourceCreator/ResourceCreator.h"
#include "../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"


using DoubleResource = std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>>;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

std::string BufferContext::BufferAssembler::ConvertName(const std::string& srcName_, const std::string& attach_)
{
	return attach_ + "[ " + srcName_ + " ] ";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::AssembleResource<ColorBuffer, ColorBufferDescription>
(
	D3D12_RESOURCE_DESC resourceDesc_,
	D3D12_HEAP_PROPERTIES heapProp_,
	const std::string& name_,
	const ColorBufferDescription& desc_
)
{
	
	//名前変換
	std::string nameCnv = ConvertName(name_, "ColorBuffer");

	//クリアバリュー必要
	auto clearValue = desc_.WatchClearValue();
	//リソース生成
	DoubleResource doubleResource = resourceCreator->Create
	(
		resourceDesc_, 
		heapProp_, 
		&clearValue,
		desc_.initialStates,
		nameCnv
	);

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
		auto accessKey = ColorBuffer::ResourceAccessKey{};
		auto instanceKey = ColorBuffer::InstanceKey{};

		//srv生成
		{
			uint32_t srvIndex{};
			D3D12_CPU_DESCRIPTOR_HANDLE srvCPU{};
			D3D12_GPU_DESCRIPTOR_HANDLE srvGPU{};

			std::tie(srvIndex, srvCPU, srvGPU) = viewCreator->CreateView(buffer_->GetResource(accessKey, i), &srvDesc);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvIndex, i);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvCPU, i);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvGPU, i);
		}

		//rtv生成
		{
			D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

			std::tie(std::ignore, rtvCPU, std::ignore) = viewCreator->CreateView(buffer_->GetResource(accessKey, i), &rtvDesc);
			buffer_->OverrideHeapIndex<ViewType::kRTV>(instanceKey, rtvCPU, i);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::AssembleResource<DepthStencilBuffer, DepthStencilBufferDescription>
(
	D3D12_RESOURCE_DESC resourceDesc_,
	D3D12_HEAP_PROPERTIES heapProp_,
	const std::string& name_,
	const DepthStencilBufferDescription& desc_
)
{
	//名前変換
	std::string nameCnv = ConvertName(name_, "DepthStencilBuffer");

	//クリアバリュー必要
	auto clearValue = desc_.WatchClearValue();
	
	//リソース生成
	DoubleResource doubleResource = resourceCreator->Create
	(
		resourceDesc_,
		heapProp_,
		&clearValue,
		desc_.initialStates,
		nameCnv
	);

	//バッファ生成
	return std::make_unique<DepthStencilBuffer>
	(
		DepthStencilBuffer::InstanceKey{},
		nameCnv,
		std::move(doubleResource.first), std::move(doubleResource.second),
		std::make_unique<DepthStencilBufferDescription>(desc_)
	);

}

template<>
void BufferContext::BufferAssembler::AssembleView<DepthStencilBuffer, DepthStencilBufferDescription>
(DepthStencilBuffer* buffer_, const DepthStencilBufferDescription& desc_)
{
	auto srvDesc = desc_.CreateSRV_Desc();
	auto dsvDesc = desc_.CreateDSVDesc();

	for (int i = 0;i < ProjectConfig::Render::kRequiredGPUBufferSum;++i)
	{
		auto accessKey = ColorBuffer::ResourceAccessKey{};
		auto instanceKey = ColorBuffer::InstanceKey{};

		//srv生成
		{
			uint32_t srvIndex{};
			D3D12_CPU_DESCRIPTOR_HANDLE srvCPU{};
			D3D12_GPU_DESCRIPTOR_HANDLE srvGPU{};

			std::tie(srvIndex, srvCPU, srvGPU) = viewCreator->CreateView(buffer_->GetResource(accessKey, i), &srvDesc);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvIndex, i);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvCPU, i);
			buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey, srvGPU, i);
		}

		//DSV生成
		{
			D3D12_CPU_DESCRIPTOR_HANDLE dsvCPU{};

			std::tie(std::ignore, dsvCPU, std::ignore) = viewCreator->CreateView(buffer_->GetResource(accessKey, i), &dsvDesc);
			buffer_->OverrideHeapIndex<ViewType::kDSV>(instanceKey, dsvCPU, i);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


