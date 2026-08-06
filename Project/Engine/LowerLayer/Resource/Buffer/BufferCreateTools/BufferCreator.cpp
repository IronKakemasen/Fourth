#include "BufferCreator.h"
#include "ResourceCreator/ResourceCreator.h"
#include "BufferAssembler/BufferAssembler.h"



BufferContext::BufferCreator::BufferCreator
(
	BufferContext::NexusFieldProof proof_,
	BufferContext::ResourceCreator* resourceCreator_,
	DescriptorHeapContextDiplomat* descriptorheapContextDiplomat_,
	BufferCollector* collector_,
	BufferDispatcher* dispatcher_
):collector(collector_), dispatcher(dispatcher_)
{
	assembler.reset(new BufferContext::BufferAssembler(proof_, resourceCreator_, descriptorheapContextDiplomat_));
	Logger::Log("Instantiate: BufferAssembler", "BufferCreator.cpp");

}

BufferContext::BufferCreator::~BufferCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
