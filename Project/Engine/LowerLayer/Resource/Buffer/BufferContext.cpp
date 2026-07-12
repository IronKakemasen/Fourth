
#include "BufferContext.h"
#include "BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

//外部
#include "../../Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"

//バッファ作成ツール
#include "BufferCreationSystems/ResourceCreator/ResourceCreator.h"
#include "BufferCreationSystems/BufferAssembler/BufferAssembler.h"
#include "BufferCreationSystems/BufferCollector/BufferCollector.h"
#include "BufferCreationSystems/BufferCreator/BufferCreator.h"

//ランタイム処理ツール
#include "RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"
#include "RuntimeBufferManagementSystems/BufferInfoExtractor/BufferInfoExtractor.h"


//ランライム

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
			&renderTargetBufferPool, 
			&computeBufferPool,
			&frameBufferPool,
			&bufferLocationMap
		)
	);

	Logger::Log("Create: bufferCollector", fileName);

	bufferCreator.reset(new BufferCreator(std::move(bufferAssembler), std::move(bufferCollector)));
	Logger::Log("Instantiate: BufferCreator", fileName);
}