#include "PreCompileHeader.h"
#include "BufferCollector.h"
#include "../GPUBuffer/GPUBufferBehavior.h"



BufferContext::BufferCollector::BufferCollector
(
	BufferContext::InstanceKey key_,
	std::vector<std::unique_ptr<GPUBufferBehavior>>* bufferContainer_,
	std::vector<GPUBufferBehavior*>* pingPongBufferPtrContainer_,
	std::vector<GPUBufferBehavior*>* frameBufferPtrContainer_
)
	:bufferContainer(bufferContainer_), pingPongBufferPtrContainer(pingPongBufferPtrContainer_), frameBufferPtrContainer(frameBufferPtrContainer_)
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

	//読み書きバッファコンテナへアドレスを配る
	for (auto itr = tmp_bufferContainer.begin();itr != tmp_bufferContainer.end();++itr)
	{
		//分別
		if ((*itr).first == RegisterType::kFrameBuffer)
		{
			frameBufferPtrContainer->emplace_back((*itr).second.get());
		}
		else
		{
			pingPongBufferPtrContainer->emplace_back((*itr).second.get());
		}

		//大本へ渡す
		bufferContainer->emplace_back(std::move((*itr).second));
	}

	tmp_bufferContainer.clear();
	tmp_bufferContainer.shrink_to_fit();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

