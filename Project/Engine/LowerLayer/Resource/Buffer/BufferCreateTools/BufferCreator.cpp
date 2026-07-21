#include "BufferCreator.h"
#include "ResourceCreator/ResourceCreator.h"
#include "BufferAssembler/BufferAssembler.h"



BufferContext::BufferCreator::BufferCreator
(
	BufferContext::InstanceKey instancekey_,
	BufferContext::ResourceCreator* resourceCreator_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
	BufferCollector* collector_
):collector(collector_)
{
	assembler.reset(new BufferContext::BufferAssembler(instancekey_, resourceCreator_, descriptorheapContextDiplomat_));
	Logger::Log("Instantiate: BufferAssembler", "BufferCreator.cpp");

}

BufferContext::BufferCreator::~BufferCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
