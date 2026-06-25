#include "PreCompileHeader.h"
#include "BufferContext.h"
#include "GPUBuffer/GPUBufferBehavior.h"

//外部
#include "../../Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"

//バッファ作成ツール
#include "ResourceCreator/ResourceCreator.h"
#include "BufferAssembler/BufferAssembler.h"
#include "BufferCollector/BufferCollector.h"
#include "BufferCreator/BufferCreator.h"

namespace
{
	std::string fileName = "BufferContext.cpp";
}

BufferContext::BufferContext
(
	InstanceKey instanceKey_, 
	CreateResourceCommand createResourceCommand_, 
	DescriptorHeapContext* descriptorHeapContext_)
{
	Logger::Entry("BufferContext: Constructor");


	InstantiateBufferCreator(instanceKey_, createResourceCommand_, descriptorHeapContext_);


	Logger::End("BufferContext: Constructor");

}

BufferContext::~BufferContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::InstantiateBufferCreator
(
	InstanceKey instanceKey_,
	CreateResourceCommand createResourceCommand_,
	DescriptorHeapContext* descriptorHeapContext_
)
{
	auto* viewCreator = descriptorHeapContext_->GetViewCreator(DescriptorHeapContext::ViewCreatorGetKey{});
	
	std::unique_ptr<ResourceCreator> resourceCreator(std::make_unique<ResourceCreator>(instanceKey_, createResourceCommand_));
	Logger::Log("Create: ResourceCreator", fileName);
	std::unique_ptr<BufferAssembler> bufferAssembler(std::make_unique<BufferAssembler>(instanceKey_, std::move(resourceCreator), viewCreator));
	Logger::Log("Create: bufferAssembler", fileName);
	std::unique_ptr<BufferCollector> bufferCollector
	(
		std::make_unique<BufferCollector>
		(
			instanceKey_, 
			&renderTargetBufferContainer, 
			&computeBufferContainer,
			&frameBufferContainer,
			&bufferLocationMap
		)
	);

	Logger::Log("Create: bufferCollector", fileName);

	bufferCreator.reset(new BufferCreator(std::move(bufferAssembler), std::move(bufferCollector)));
	Logger::Log("Instantiate: BufferCreator", fileName);
}