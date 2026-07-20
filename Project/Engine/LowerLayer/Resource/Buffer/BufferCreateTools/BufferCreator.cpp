#include "BufferCreator.h"
#include "ResourceCreator/ResourceCreator.h"
#include "BufferAssembler/BufferAssembler.h"



BufferContext::BufferCreator::BufferCreator
(
	BufferContext::InstanceKey instancekey_,
	BufferContext::ResourceCreator* resourceCreator_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
	BufferPoolSet* bufferPoolSet_
) 
{
	assembler.reset(new BufferContext::BufferAssembler(instancekey_, resourceCreator_, descriptorheapContextDiplomat_));
	Logger::Log("Instantiate: BufferAssembler", "BufferCreator.cpp");
	
	collector.reset(new BufferContext::BufferCollector(instancekey_,bufferPoolSet_));
	Logger::Log("Instantiate: bufferCollector", "BufferCreator.cpp");

}

BufferContext::BufferCreator::~BufferCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
