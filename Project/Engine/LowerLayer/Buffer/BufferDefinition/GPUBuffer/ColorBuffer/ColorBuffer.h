#pragma once
#include "../GPUBufferBehavior.h"
#include "../BufferInterface.h"

//カラーバッファクラス
class ColorBuffer final : public GPUBufferBehavior, public IColorBuffer, public IRenderTarget,public IReadable
{

public:

	ColorBuffer
	(
		const InstanceKey& instanceKey_,
		std::string const& name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		const BufferDescriptionBehavior& description_
	);

	//バリア生成
	virtual std::optional<D3D12_RESOURCE_BARRIER> CreateBarrier(BufferUsage usage_) override;
	//適切なRTVヒープインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperRTVHeapHandle()const override;
	//適切なSRVヒープインデックスを出す
	virtual SRVHeapIndex OutProperSRVHeapIndex(int frameIndex_ = 0)const override;
};



