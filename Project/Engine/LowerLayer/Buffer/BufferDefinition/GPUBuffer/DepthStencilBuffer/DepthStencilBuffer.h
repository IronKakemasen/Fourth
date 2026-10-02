#pragma once
#include "../GPUBufferBehavior.h"
#include "../BufferInterface.h"


//定数バッファクラス
class DepthStencilBuffer final : public GPUBufferBehavior, public IDepthBuffer, public IRenderTarget, public IReadable
{

public:

	DepthStencilBuffer
	(
		const InstanceKey& instanceKey_,
		std::string const& name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		const BufferDescriptionBehavior& description_
	);

	//バリアを張る
	virtual std::optional<D3D12_RESOURCE_BARRIER> CreateBarrier(BufferUsage usage_) override;
	//適切なCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperDSVHeapHandle()const override;
	//適切なsrvHeapインデックスを渡す
	virtual SRVHeapIndex OutProperSRVHeapIndex(int frameIndex_ = 0)const override;
};

