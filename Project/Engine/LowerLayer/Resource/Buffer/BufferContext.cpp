#include "BufferContext.h"
#include "BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
//バッファ作成ツール
#include "BufferCreateTools/BufferCreator.h"
//バッファをアップロード
#include "BufferCreateTools/BufferUploader/BufferUploader.h"
//各種ツールを下位部へ貸し出します
#include "BufferToolLender/BufferToolLender.h"
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
	DeviceContextDiplomat* deviceContextDiplomat_,
	DescriptorHeapContext* descriptorHeapContext_,
	CommandContextDiplomat* commandContextDiplomat_
)
{
	Logger::Entry("BufferContext: Constructor");

	resourceCreator.reset(new BufferContext::ResourceCreator(instanceKey_, deviceContextDiplomat_));
	Logger::Log("Instantiate: ResourceCreator", fileName);

	bufferCreator.reset(new BufferCreator(instanceKey_, resourceCreator.get(), descriptorHeapContext_, &bufferPoolSet));
	Logger::Log("Instantiate: BufferCreator", fileName);

	bufferUploader.reset(new BufferUploader(instanceKey_, resourceCreator.get(),bufferDispatcher.get(), commandContextDiplomat_));
	Logger::Log("Instantiate: BufferUploader", fileName);

	toolLender.reset(new ToolLender(instanceKey_, bufferCreator.get(), bufferUploader.get()));
	Logger::Log("Instantiate: ToolLender", fileName);


	Logger::End("BufferContext: Constructor");

}

BufferContext::~BufferContext()
{

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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::DeleteBufferUploader(const InstanceKey& key_)
{
	///中にある中間リソースをすべて削除
	bufferUploader.reset();
	Logger::Log("delete: bufferUploader", fileName);
}
