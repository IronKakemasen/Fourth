#include "BufferCollector.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"
#include "ClosedHashMap/ClosedHashMap.h" 

//バッファ群
#include "../../BufferDefinition/AllBuffersInclude.h"

BufferContext::BufferCollector::BufferCollector
(
	BufferContext::NexusFieldProof proof_,
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
template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<ColorBuffer> buffer_)
{
	return std::move(std::unique_ptr<GPUBufferBehavior>(std::move(buffer_)));
}

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<ConstantBuffer> buffer_)
{
	return std::move(std::unique_ptr<GPUBufferBehavior>(std::move(buffer_)));
}

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<ComputeBuffer> buffer_)
{
	return std::move(std::unique_ptr<GPUBufferBehavior>(std::move(buffer_)));
}

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<DepthStencilBuffer> buffer_)
{
	return std::move(std::unique_ptr<GPUBufferBehavior>(std::move(buffer_)));
}

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<UploadStructuredBuffer> buffer_)
{
	return std::move(std::unique_ptr<GPUBufferBehavior>(std::move(buffer_)));
}

template<>
std::unique_ptr<GPUBufferBehavior> BufferContext::BufferCollector::CastBuffer(std::unique_ptr<StaticStructuredBuffer> buffer_)
{
	return std::unique_ptr<GPUBufferBehavior>(std::move(buffer_));
}
