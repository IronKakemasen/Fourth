#include "BufferAssembler.h"
#include "../../BufferDefinition/AllBuffersInclude.h"
#include "../../BufferDefinition/AllBufferDescsInclude.h"

#include "BufferAssemblerTools/ResourceAssembler/ResourceAssembler.h"
#include "BufferAssemblerTools/BufferNameConverter/BufferNameConverter.h"
#include "BufferAssemblerTools/BufferMaterializer/BufferMaterializer.h"
#include "BufferAssemblerTools/ViewAssembler/ViewAssembler.h"


//外部
#include "../../../../Core/DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapContextDiplomat.h"
#include "../../../../Core/DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLender.h"

namespace
{
	auto const fileName = "BufferAssembler.cpp";
}


BufferContext::BufferAssembler::BufferAssembler
(
	BufferContext::NexusFieldProof proof_,
	ResourceCreator* resourceCreator_, 
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_
)
	:resourceCreator(resourceCreator_)
{
	//ビュークリエイターを借りる
	auto* toolLender = descriptorheapContextDiplomat_->Access<DescriptorHeapContext::ToolLender>();
	DescriptorHeapContext::ToolLender::LicenceType<DescriptorHeapContext::ViewCreator> licence;
	viewCreator = toolLender->Lend<DescriptorHeapContext::ViewCreator>(licence);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
	const std::string& nameCnv_,
	const ColorBufferDescription& desc_
)
{
	return ResourceAssembler::AssembleResource
	(
		*resourceCreator,
		nameCnv_,
		desc_
	);
}

template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
	const std::string& nameCnv_,
	const DepthStencilBufferDescription& desc_
)
{
	return ResourceAssembler::AssembleResource
	(
		*resourceCreator,
		nameCnv_,
		desc_
	);
}

template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
	const std::string& nameCnv_,
	const ConstantBufferDescription& desc_
)
{
	return ResourceAssembler::AssembleResource
	(
		*resourceCreator,
		nameCnv_,
		desc_
	);
}

template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
	const std::string& nameCnv_,
	const ComputeBufferDescription& desc_
)
{
	return ResourceAssembler::AssembleResource
	(
		*resourceCreator,
		nameCnv_,
		desc_
	);
}

template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
	const std::string& nameCnv_,
	const StaticStructuredBufferDescription& desc_
)
{
	return ResourceAssembler::AssembleResource
	(
		*resourceCreator,
		nameCnv_,
		desc_
	);
}

template<>
BufferContext::BufferAssembler::ResourceContainer BufferContext::BufferAssembler::AssembleResource
(
	const std::string& nameCnv_,
	const UploadStructuredBufferDescription& desc_
)
{
	return ResourceAssembler::AssembleResource
	(
		*resourceCreator,
		nameCnv_,
		desc_
	);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::string BufferContext::BufferAssembler::ConvertName<ColorBuffer>(const std::string& srcName_)
{
	return BufferNameConverter::ConvertName<ColorBuffer>(srcName_);
}
template<>
std::string BufferContext::BufferAssembler::ConvertName<DepthStencilBuffer>(const std::string& srcName_)
{
	return BufferNameConverter::ConvertName<DepthStencilBuffer>(srcName_);
}
template<>
std::string BufferContext::BufferAssembler::ConvertName<ConstantBuffer>(const std::string& srcName_)
{
	return BufferNameConverter::ConvertName<ConstantBuffer>(srcName_);
}

template<>
std::string BufferContext::BufferAssembler::ConvertName<StaticStructuredBuffer>(const std::string& srcName_)
{
	return BufferNameConverter::ConvertName<StaticStructuredBuffer>(srcName_);
}

template<>
std::string BufferContext::BufferAssembler::ConvertName<UploadStructuredBuffer>(const std::string& srcName_)
{
	return BufferNameConverter::ConvertName<UploadStructuredBuffer>(srcName_);
}

template<>
std::string BufferContext::BufferAssembler::ConvertName<ComputeBuffer>(const std::string& srcName_)
{
	return BufferNameConverter::ConvertName<ComputeBuffer>(srcName_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
std::unique_ptr<ColorBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_)
{
	return std::move(BufferMaterializer::Materialize<ColorBuffer>(std::move(resourceContainer_), desc_, nameCnv_));
}
template<>
std::unique_ptr<DepthStencilBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_)
{
	return std::move(BufferMaterializer::Materialize<DepthStencilBuffer>(std::move(resourceContainer_), desc_, nameCnv_));
}
template<>
std::unique_ptr<StaticStructuredBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_)
{
	return std::move(BufferMaterializer::Materialize<StaticStructuredBuffer>(std::move(resourceContainer_), desc_, nameCnv_));
}
template<>
std::unique_ptr<ConstantBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_)
{
	return std::move(BufferMaterializer::Materialize<ConstantBuffer>(std::move(resourceContainer_), desc_, nameCnv_));
}
template<>
std::unique_ptr<UploadStructuredBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_)
{
	return std::move(BufferMaterializer::Materialize<UploadStructuredBuffer>(std::move(resourceContainer_), desc_, nameCnv_));
}
template<>
std::unique_ptr<ComputeBuffer> BufferContext::BufferAssembler::Materialize(ResourceContainer resourceContainer_, const BufferDescriptionBehavior& desc_, std::string nameCnv_)
{
	return std::move(BufferMaterializer::Materialize<ComputeBuffer>(std::move(resourceContainer_), desc_, nameCnv_));
}
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
)
{
	return ViewAssembler::AssembleView
	(
		accessKey_,
		instanceKey_,
		*viewCreator,
		buffer_,
		desc_
	);
}
template<>
void BufferContext::BufferAssembler::AssembleView
(
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_,
	GPUBufferBehavior* buffer_,
	const DepthStencilBufferDescription& desc_
)
{
	return ViewAssembler::AssembleView
	(
		accessKey_,
		instanceKey_,
		*viewCreator,
		buffer_,
		desc_
	);
}
template<>
void BufferContext::BufferAssembler::AssembleView
(
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_,
	GPUBufferBehavior* buffer_,
	const UploadStructuredBufferDescription& desc_
)
{
	return ViewAssembler::AssembleView
	(
		accessKey_,
		instanceKey_,
		*viewCreator,
		buffer_,
		desc_
	);
}
template<>
void BufferContext::BufferAssembler::AssembleView
(
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_,
	GPUBufferBehavior* buffer_,
	const ComputeBufferDescription& desc_
)
{
	return ViewAssembler::AssembleView
	(
		accessKey_,
		instanceKey_,
		*viewCreator,
		buffer_,
		desc_
	);
}
template<>
void BufferContext::BufferAssembler::AssembleView
(
	GPUBufferBehavior::ResourceAccessKey accessKey_,
	GPUBufferBehavior::InstanceKey instanceKey_,
	GPUBufferBehavior* buffer_,
	const StaticStructuredBufferDescription& desc_
)
{
	return ViewAssembler::AssembleView
	(
		accessKey_,
		instanceKey_,
		*viewCreator,
		buffer_,
		desc_
	);
}
