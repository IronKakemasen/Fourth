#pragma once
#include "../BufferInterface.h"


//定数バッファクラス
class DepthStencilBuffer final : public GPUBufferBehavior, IRenderTargetBuffer,IShaderBuffer,IDepthBuffer
{
	friend class BufferContext::BufferInfoExtractor;

public:

	DepthStencilBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

private:

	//バリアを張る
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) override;
	//適切なCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperDSVHeapHandle()const override;
	//適切なsrvHeapインデックスを渡す
	virtual SRVHeapIndex OutProperSRVHeapIndex(int frameIndex_ = 0)const override;
};

