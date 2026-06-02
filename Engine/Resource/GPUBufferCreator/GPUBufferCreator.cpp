#include "PreCompileHedder.h"
#include "GPUBufferCreator.h"

void GPUBufferCreator::CheckDescription(BufferDescriptionBehavior* srcDesc_)
{
	srcDesc_->CheckRequirementsFilled();
}

GPUBufferCreator::GPUBufferCreator(GPUBufferCreator::CreateKey createKey_)
{

}