#include "BufferCollector.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
#include "ClosedHashMap/ClosedHashMap.h" 


BufferContext::BufferCollector::BufferCollector
(
	BufferContext::InstanceKey key_,
	BufferContext::BufferPoolSet* bufferPoolSet_
):bufferPoolSet(bufferPoolSet_)
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
		auto* dstContainer = bufferPoolSet->ContainerTable((*itrSrcContainer).type);

		//空きスロットを検索
		//auto itrDstConatiner = FindFreeSlot(dstContainer);

		///バッファは削除しない、使いまわさない条約が決定したので全部けつに突っ込む
		dstContainer->emplace_back(std::move((*itrSrcContainer).buffer));
		//ユニークIDとコンテナ上のIDを紐づける 
		///bufferLocationClosedHashedMapの開いてる場所
		auto freeIndex = bufferPoolSet->bufferLocationClosedHashedMap->CheckDuplication((*itrSrcContainer).id).second.value();
		//bufferContainerのけつのインデックス
		uint32_t lastIndex = int32_t(dstContainer->size() - 1);
		bufferPoolSet->bufferLocationClosedHashedMap->Insert(freeIndex, (*itrSrcContainer).id, { (*itrSrcContainer).type ,lastIndex });


	}

	tmp_bufferContainer.clear();
	tmp_bufferContainer.shrink_to_fit();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
