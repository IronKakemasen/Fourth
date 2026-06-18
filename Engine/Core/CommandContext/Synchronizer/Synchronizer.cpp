#include "PreCompileHeader.h"
#include "Synchronizer.h"



CommandContext::Synchronizer::Synchronizer
(
	ID3D12CommandQueue* commandQueue_,
	ID3D12Fence* fence_,
	std::array<uint64_t, ProjectConfig::Render::kRequiredGPUBufferSum>* fenceCounters_,
	HANDLE* fenceEvent_
):commandQueue(commandQueue_), fence(fence_), fenceCounters(fenceCounters_), fenceEvent(fenceEvent_)
{

}

void CommandContext::Synchronizer::Synchronize(UINT frameIndex_)
{
	auto currentValue = (*fenceCounters).at(frameIndex_);

	commandQueue->Signal(fence, currentValue);

	if (fence->GetCompletedValue() < currentValue)
	{
		//指定したSignalにたどり着いていないので、たどり着くまで待つ
		fence->SetEventOnCompletion(currentValue, *fenceEvent);
		//イベント待つ
		WaitForSingleObjectEx(*fenceEvent, INFINITE, FALSE);
	}

	// 次のフレームのフェンスカウンターを増やす
	(*fenceCounters).at(frameIndex_) = currentValue + 1;

}