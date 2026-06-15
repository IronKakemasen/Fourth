#include "PreCompileHedder.h"
#include "BufferContext.h"
#include "ResourceCreator/ResourceCreator.h"
#include "BufferAssembler/BufferAssembler.h"
#include "../Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../Core/DescriptorHeap/ViewCreator/ViewCreator.h"


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

	std::unique_ptr<ResourceCreator> resourceCreator(std::make_unique<ResourceCreator>(instanceKey_, createResourceCommand_));
	auto* viewCreator = descriptorHeapContext_->ShareViewCreator(DescriptorHeapContext::ViewCreatorShareKey{});

	bufferAssembler.reset(new BufferAssembler(instanceKey_, std::move(resourceCreator), viewCreator));
	Logger::Log("Create: bufferAssembler", fileName);

	Logger::End("BufferContext: Constructor");

}

BufferContext::~BufferContext()
{

}