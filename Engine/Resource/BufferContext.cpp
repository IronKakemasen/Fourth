#include "PreCompileHedder.h"
#include "BufferContext.h"
#include "ResourceCreator/ResourceCreator.h"


BufferContext::BufferContext(InstanceKey instanceKey_, CreateResourceCommand createResourceCommand_)
{
	resourceCreator.reset(new ResourceCreator(instanceKey_, createResourceCommand_)) ;
}

BufferContext::~BufferContext()
{

}