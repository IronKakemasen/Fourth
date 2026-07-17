#include "BufferContext.h"
#include "BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

//外部
#include "../../Core/DescriptorHeap/DescriptorHeapContext.h"
#include "../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"

//バッファ作成ツール
#include "BufferCreator/BufferCreator.h"

//ランタイム処理ツール
#include "RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"
#include "RuntimeBufferManagementSystems/BufferInfoExtractor/BufferInfoExtractor.h"

#include "ClosedHashMap/ClosedHashMap.h" 


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
	
	bufferCreator.reset(new BufferCreator(instanceKey_, createResourceCommand_,viewCreator,&bufferPoolSet));
	Logger::Log("Instantiate: BufferCreator", fileName);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::unique_ptr<GPUBufferBehavior>>* BufferContext::BufferPoolSet::ContainerTable(BufferContext::RegisterType type_)
{
	static std::vector<std::unique_ptr<GPUBufferBehavior>>* table[(int)BufferContext::RegisterType::kCount]
	{
		&renderTargetBufferPool,
		&frameBufferPool,
		&computeBufferPool,
		&readOnlyBufferPool
	};

	return table[(int)type_];
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BufferContext::BufferPoolSet::BufferPoolSet()
{
	bufferLocationClosedHashedMap.reset(new ClosedHashMap<std::pair<RegisterType, uint32_t>>(kHashedMapSize));
}