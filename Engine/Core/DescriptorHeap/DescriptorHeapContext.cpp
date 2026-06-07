#include "PreCompileHedder.h"
#include "DescriptorHeapContext.h"
#include "DescriptorHeapCreator/DescriptorHeapCreator.h"

DescriptorHeapContext::DescriptorHeapContext(InstanceKey instanceKey_)
{
	Logger::Entry("DescriptorHeapContext::Constructor");

	descriptorHeapCreator.reset(new DescriptorHeapCreator(instanceKey_));
	Logger::Log("Instantiate : DescriptorHeapCreator");


	Logger::End("DescriptorHeapContext::Constructor");
}

DescriptorHeapContext::~DescriptorHeapContext()
{

}

void DescriptorHeapContext::SetCommand(DescroptorCreateCommand createFunc_)
{
	descriptorHeapCreator->SetCommand(createFunc_);
}

void DescriptorHeapContext::CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible_)
{
	descriptorHeaps[heapType_] = std::move(descriptorHeapCreator->createFunc(heapType_, numDescriptors_, shaderVisible_));
}
