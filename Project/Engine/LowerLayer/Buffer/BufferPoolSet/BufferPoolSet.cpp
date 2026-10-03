#include "PreCompileHeader.h"
#include "BufferPoolSet.h"
#include "ClosedHashMap/ClosedHashMap.h" 
#include "../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

std::vector<std::unique_ptr<GPUBufferBehavior>>* BufferContext::BufferPoolSet::ContainerTable(BufferTraits::RegisterType type_)
{
	static std::vector<std::unique_ptr<GPUBufferBehavior>>* table[(int)BufferTraits::RegisterType::kCount]
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
	bufferLocationClosedHashedMap.reset(new ClosedHashMap<std::pair<BufferTraits::RegisterType, uint32_t>>(kHashedMapSize));
}
