#pragma once
#include "../CommandContext.h"

class CommandContext::Builder
{
	struct Output
	{
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		//コマンドアローケータ
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer> commandAllocators;
		//コマンドリスト		
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6> commandList;
		//フェンスイベント
		HANDLE fenceEvent;
		//フェンス
		Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
		//RuntimeCommandController
		std::unique_ptr<RuntimeCommandController> runtimeCommandController;
	};

	friend class CommandContext;

	static Output CreateCoreParts
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat& deviceContextDiplomat_
	);

};


