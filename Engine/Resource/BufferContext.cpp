#include "PreCompileHedder.h"
#include "BufferContext.h"
#include "GPUBufferCreator/GPUBufferCreator.h"


BufferContext::BufferContext(InstanceKey instanceKey_, CreateResourceCommand createResourceCommand_)
{
	gpuBufferCreator.reset(new GPUBufferCreator(instanceKey_, createResourceCommand_)) ;
}

BufferContext::~BufferContext()
{

}