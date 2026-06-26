#pragma once
#include "../CommandContext.h"

class CommandContext::Synchronizer
{
public:

	Synchronizer
	(
		ID3D12CommandQueue* commandQueue_,
		ID3D12Fence* fence_,
		std::array<uint64_t, ProjectConfig::Render::kDoubleBuffer>* fenceCounters_,
		HANDLE* fenceEvent_,
		uint64_t* commonFenceValue_
	);

	void InsertSignal(UINT frameIndex_);
	void Wait(UINT frameIndex_);
	void WaitDirectly();

private:
	ID3D12CommandQueue* commandQueue;
	ID3D12Fence* fence;
	std::array<uint64_t, ProjectConfig::Render::kDoubleBuffer>* fenceCounters;
	HANDLE* fenceEvent;
	uint64_t* commonFenceValue = 0;


};

