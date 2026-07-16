#pragma once
#include "../BufferInterface.h"

//カラーバッファクラス
class ColorBuffer final : public GPUBufferBehavior,IColorBuffer,IRenderTargetBuffer,IShaderBuffer
{
	friend class BufferContext::BufferInfoExtractor;

public:

	ColorBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);


private:
	//バリア生成
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) override;
	//適切なRTVヒープインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperRTVHeapHandle()const override;
	//適切なSRVヒープインデックスを出す
	virtual SRVHeapIndex OutProperSRVHeapIndex(int frameIndex_ = 0)const override;
};



