
#include "BufferAssembler.h"

//バッファ
#include "../../BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../BufferDefinition/GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../../BufferDefinition/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"
#include "../../BufferDefinition/GPUBuffer/ComputeBuffer/ComputeBuffer.h"
#include "../../BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"
#include"../../BufferDefinition/GPUBuffer/StaticStructuredBuffer/StaticStructuredBuffer.h"

//ディスクリプション
#include "../../BufferDefinition/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../BufferDefinition/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"
#include "../../BufferDefinition/BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"
#include "../../BufferDefinition/BufferDescriptions/ComputeBufferDescription/ComputeBufferDescription.h"
#include "../../BufferDefinition/BufferDescriptions/UploadStructuredBufferDescription/UploadStructuredBufferDescription.h"
#include "../../BufferDefinition/BufferDescriptions/StaticStructuredBufferDescription/StaticStructuredBufferDescription.h"

//ツール
#include "../../../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"

namespace
{
	auto const fileName = "BufferAssembler.cpp";
}


BufferContext::BufferAssembler::BufferAssembler
(
	BufferContext::InstanceKey instancekey_, 
	CreateResourceCommand createResourceCommand_,
	ViewCreator* viewCreator_
)
	:viewCreator(viewCreator_)
{
	resourceCreator.reset(new BufferContext::ResourceCreator(instancekey_, createResourceCommand_));
	Logger::Log("Instantiate: BufferAssembler", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::pair<D3D12_RESOURCE_DESC, D3D12_HEAP_PROPERTIES> BufferContext::BufferAssembler::AssembleResourceCreateRequirements(const BufferDescriptionBehavior& desc_)
{
	//要項チェック
	desc_.CheckRequirementsFilled();
	Logger::Log("Check: RequirementsFilled", fileName);

	D3D12_HEAP_PROPERTIES heapProp = desc_.CreateHeapProperties();
	Logger::Log("Create: heapProp", fileName);

	D3D12_RESOURCE_DESC resourceDesc = desc_.CreateResourceDesc();
	Logger::Log("Create: resourceDesc", fileName);

	return std::make_pair(resourceDesc, heapProp);
}


///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ColorBufferDescription& desc_)
{
	return desc_.WatchClearValue();
}

template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::AssembleBuffer<ColorBuffer, ColorBufferDescription>
(ResourceContainer resourceContainer_, const ColorBufferDescription& desc_, std::string nameCnv_)
{
	//バッファ生成
	return std::make_unique<ColorBuffer>
	(
	    ColorBuffer::InstanceKey{},
	    nameCnv_,
	    std::move(resourceContainer_),
	    std::make_unique<ColorBufferDescription>(desc_)
	);
}

template<>
void BufferContext::BufferAssembler::AssembleView<ColorBuffer, ColorBufferDescription>
(ColorBuffer* buffer_, const ColorBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_)
{
	auto srvDesc = desc_.CreateSRV_Desc();
	auto rtvDesc = desc_.CreateRTV_Desc();

	for (int i = 0;i < desc_.numBuffer;++i)
	{
		//srv作成
		CreateView(buffer_, srvDesc, i, accessKey_, instanceKey_);
		Logger::Log("Create: srv", fileName);
		//UAV生成
		CreateView(buffer_, rtvDesc, i, accessKey_, instanceKey_);
		Logger::Log("Create: rtv", fileName);

	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const DepthStencilBufferDescription& desc_)
{
	return desc_.WatchClearValue();
}

template<>
std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::AssembleBuffer<DepthStencilBuffer, DepthStencilBufferDescription>
(ResourceContainer resourceContainer_, const DepthStencilBufferDescription& desc_, std::string nameCnv_)
{
	//バッファ生成
	return std::make_unique<DepthStencilBuffer>
	(
		DepthStencilBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		std::make_unique<DepthStencilBufferDescription>(desc_)
	);
}

template<>
void BufferContext::BufferAssembler::AssembleView<DepthStencilBuffer, DepthStencilBufferDescription>
(DepthStencilBuffer* buffer_, const DepthStencilBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_)
{
	auto srvDesc = desc_.CreateSRV_Desc();
	auto dsvDesc = desc_.CreateDSVDesc();

	for (int i = 0;i < desc_.numBuffer;++i)
	{
		//srv作成
		CreateView(buffer_, srvDesc, i, accessKey_, instanceKey_);
		Logger::Log("Create: srv", fileName);
		//DSV生成
		CreateView(buffer_, dsvDesc, i, accessKey_, instanceKey_);
		Logger::Log("Create: dsv", fileName);

	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ConstantBufferDescription& desc_)
{
	return std::nullopt;
}
	
template<>
std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::AssembleBuffer<ConstantBuffer, ConstantBufferDescription>
(ResourceContainer resourceContainer_, const ConstantBufferDescription& desc_, std::string nameCnv_)
{
	//バッファ生成
	return std::make_unique<ConstantBuffer>
	(
		ConstantBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		std::make_unique<ConstantBufferDescription>(desc_)
	);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const ComputeBufferDescription& desc_)
{
	return std::nullopt;
}

template<>
std::unique_ptr<ComputeBuffer> BufferContext::BufferAssembler::AssembleBuffer<ComputeBuffer, ComputeBufferDescription>
(ResourceContainer resourceContainer_, const ComputeBufferDescription& desc_, std::string nameCnv_)
{
	//バッファ生成
	return std::make_unique<ComputeBuffer>
	(
		ComputeBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		std::make_unique<ComputeBufferDescription>(desc_)
	);
}

template<>
void BufferContext::BufferAssembler::AssembleView<ComputeBuffer, ComputeBufferDescription>
(ComputeBuffer* buffer_, const ComputeBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_)
{
	auto srvDesc = desc_.CreateSRV_Desc();
	auto uavDesc = desc_.CreateUAV_Desc();

	for (int i = 0;i < desc_.numBuffer;++i)
	{
		//srv作成
		CreateView(buffer_, srvDesc, i, accessKey_, instanceKey_);
		Logger::Log("Create: srv", fileName);
		//UAV生成
		CreateView(buffer_, uavDesc, i, accessKey_, instanceKey_);
		Logger::Log("Create: uav", fileName);
	}

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const StaticStructuredBufferDescription& desc_)
{
	return std::nullopt;
}

template<>
void BufferContext::BufferAssembler::AssembleView<StaticStructuredBuffer, StaticStructuredBufferDescription>
(StaticStructuredBuffer* buffer_, const StaticStructuredBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_)
{
	auto srvDesc = desc_.CreateSRV_Desc();

	//srv作成
	CreateView(buffer_, srvDesc, 0, accessKey_, instanceKey_);
	Logger::Log("Create: srv", fileName);

}

template<>
std::unique_ptr<StaticStructuredBuffer> BufferContext::BufferAssembler::AssembleBuffer<StaticStructuredBuffer, StaticStructuredBufferDescription>
(ResourceContainer resourceContainer_, const StaticStructuredBufferDescription& desc_, std::string nameCnv_)
{
	//バッファ生成
	return std::make_unique<StaticStructuredBuffer>
	(
		StaticStructuredBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		std::make_unique<StaticStructuredBufferDescription>(desc_)
	);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::optional<D3D12_CLEAR_VALUE> BufferContext::BufferAssembler::GetClearValue(const UploadStructuredBufferDescription& desc_)
{
	return std::nullopt;

}

template<>
void BufferContext::BufferAssembler::AssembleView<UploadStructuredBuffer, UploadStructuredBufferDescription>
(UploadStructuredBuffer* buffer_, const UploadStructuredBufferDescription& desc_, GPUBufferBehavior::ResourceAccessKey accessKey_, GPUBufferBehavior::InstanceKey instanceKey_)
{
	auto srvDesc = desc_.CreateSRV_Desc();

	//srv作成
	CreateView(buffer_, srvDesc, 0, accessKey_, instanceKey_);
	Logger::Log("Create: srv", fileName);
	//srv生成
	CreateView(buffer_, srvDesc, 1, accessKey_, instanceKey_);
	Logger::Log("Create: srv", fileName);
}

template<>
std::unique_ptr<UploadStructuredBuffer> BufferContext::BufferAssembler::AssembleBuffer<UploadStructuredBuffer, UploadStructuredBufferDescription>
(ResourceContainer resourceContainer_, const UploadStructuredBufferDescription& desc_, std::string nameCnv_)
{
	//バッファ生成
	return std::make_unique<UploadStructuredBuffer>
	(
		UploadStructuredBuffer::InstanceKey{},
		nameCnv_,
		std::move(resourceContainer_),
		std::make_unique<UploadStructuredBufferDescription>(desc_)
	);

}
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
)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvCPU{};

	std::tie(std::ignore, rtvCPU, std::ignore) = viewCreator->CreateView(buffer_->GetResource(accessKey_, index_), &desc_);
	buffer_->OverrideHeapIndex<ViewType::kRTV>(instanceKey_, rtvCPU, index_);
}

template<>
void BufferContext::BufferAssembler::CreateView
(
	GPUBufferBehavior* buffer_,
	const D3D12_DEPTH_STENCIL_VIEW_DESC& desc_,
	uint8_t index_,
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_
)
{
	D3D12_CPU_DESCRIPTOR_HANDLE dsvCPU{};

	std::tie(std::ignore, dsvCPU, std::ignore) = viewCreator->CreateView(buffer_->GetResource(accessKey_, index_), &desc_);
	buffer_->OverrideHeapIndex<ViewType::kDSV>(instanceKey_, dsvCPU, index_);
}

template<>
void BufferContext::BufferAssembler::CreateView
(
	GPUBufferBehavior* buffer_,
	const D3D12_SHADER_RESOURCE_VIEW_DESC& desc_,
	uint8_t index_,
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_
)
{

	uint32_t srvIndex{};
	D3D12_CPU_DESCRIPTOR_HANDLE srvCPU{};
	D3D12_GPU_DESCRIPTOR_HANDLE srvGPU{};

	std::tie(srvIndex, srvCPU, srvGPU) = viewCreator->CreateView(buffer_->GetResource(accessKey_, index_), &desc_);
	buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey_, srvIndex, index_);
	buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey_, srvCPU, index_);
	buffer_->OverrideHeapIndex<ViewType::kSRV>(instanceKey_, srvGPU, index_);
}

template<>
void BufferContext::BufferAssembler::CreateView
(
	GPUBufferBehavior* buffer_,
	const D3D12_UNORDERED_ACCESS_VIEW_DESC& desc_,
	uint8_t index_,
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_
)
{
	uint32_t uavIndex{};
	D3D12_CPU_DESCRIPTOR_HANDLE uavCPU{};
	D3D12_GPU_DESCRIPTOR_HANDLE uavGPU{};

	std::tie(uavIndex, uavCPU, uavGPU) = viewCreator->CreateView(buffer_->GetResource(accessKey_, index_), &desc_);
	buffer_->OverrideHeapIndex<ViewType::kUAV>(instanceKey_, uavIndex, index_);
	buffer_->OverrideHeapIndex<ViewType::kUAV>(instanceKey_, uavCPU, index_);
	buffer_->OverrideHeapIndex<ViewType::kUAV>(instanceKey_, uavGPU, index_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
