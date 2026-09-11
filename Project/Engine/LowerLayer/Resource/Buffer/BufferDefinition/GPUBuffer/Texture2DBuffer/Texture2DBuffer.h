#pragma once
#include "../BufferInterface.h"



//2Dテクスチャバッファ
class Texture2DBuffer final : public GPUBufferBehavior, IReadable, public IReadOnly
{
	friend class BufferContext::BufferInfoExtractor;

public:

	Texture2DBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		const BufferDescriptionBehavior& description_
	);


private:
	//適切なSRVヒープインデックスを出す
	virtual SRVHeapIndex OutProperSRVHeapIndex(int frameIndex_ = 0)const override;
	virtual D3D12_RESOURCE_BARRIER CreateBarrierAsReading()override;

};



