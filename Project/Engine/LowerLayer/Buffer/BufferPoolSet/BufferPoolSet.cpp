#include "PreCompileHeader.h"
#include "BufferPoolSet.h"
#include "ClosedHashMap/ClosedHashMap.h" 
#include "../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

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
