#pragma once
#include "../BufferInterface.h"


//読み込み専用StructuredBuffer
class StaticStructuredBuffer final : public GPUBufferBehavior, IReadable,IReadOnly
{

public:

	StaticStructuredBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		const BufferDescriptionBehavior& description_
	);

	virtual ~StaticStructuredBuffer() = default;

	virtual SRVHeapIndex OutProperSRVHeapIndex(int frameIndex_ = 0)const override;
	virtual D3D12_RESOURCE_BARRIER CreateBarrierAsReading()override;

};

