#include "PreCompileHeader.h"
#include "BufferCollector.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"



BufferContext::BufferCollector::BufferCollector
(
	BufferContext::InstanceKey key_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* renderTargetBufferContainer_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* computeBufferContainer_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* frameBufferContainer_,
	std::unordered_map<BufferContext::BufferUniqueID, std::pair<RegisterType, uint32_t>>* bufferLocationMap_
):renderTargetBufferContainer(renderTargetBufferContainer_), computeBufferContainer(computeBufferContainer_), frameBufferContainer(frameBufferContainer_), bufferLocationMap(bufferLocationMap_)
{

}

BufferContext::BufferCollector::~BufferCollector()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferCollector::Distribute()
{
	if (tmp_bufferContainer.size() == 0) return;

	//適切なバッファコンテナへ実体を渡す
	for (auto itrSrcContainer = tmp_bufferContainer.begin();itrSrcContainer != tmp_bufferContainer.end();++itrSrcContainer)
	{
		//コンテナ取得
		auto* dstContainer = ContainerTable((*itrSrcContainer).type);

		//空きスロットを検索
		auto itrDstConatiner = FindFreeSlot(dstContainer);

		//空きスロットに入れる
		if (itrDstConatiner != dstContainer->end())
		{
			//そのイテレーターをリセットする
			itrDstConatiner->reset();

			(*itrDstConatiner) = std::move((*itrSrcContainer).buffer);
			//該当の空きインデックス
			uint32_t freeIndex = uint32_t(itrDstConatiner - dstContainer->begin());
			//ユニークIDとコンテナ上のIDを紐づける 
			(*bufferLocationMap)[(*itrSrcContainer).id] = std::make_pair((*itrSrcContainer).type, freeIndex);
		}
		//空きスロットが無ければ尻尾に追加
		else
		{
			dstContainer->emplace_back(std::move((*itrSrcContainer).buffer));
			//ユニークIDとコンテナ上のIDを紐づける 
			(*bufferLocationMap)[(*itrSrcContainer).id] = std::make_pair((*itrSrcContainer).type, uint32_t(dstContainer->size() - 1 ));

		}
	}

	tmp_bufferContainer.clear();
	tmp_bufferContainer.shrink_to_fit();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::unique_ptr<GPUBufferBehavior>>* BufferContext::BufferCollector::ContainerTable(BufferContext::RegisterType type_)
{
	static std::vector<std::unique_ptr<GPUBufferBehavior>>* table[(int)BufferContext::RegisterType::kCount]
	{
		renderTargetBufferContainer,
		frameBufferContainer,
		computeBufferContainer
	};

	return table[(int)type_];
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::unique_ptr<GPUBufferBehavior>>::iterator BufferContext::BufferCollector::FindFreeSlot(std::vector<std::unique_ptr<GPUBufferBehavior>>* container_)
{
	return std::find(container_->begin(), container_->end(), nullptr);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

