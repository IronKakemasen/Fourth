#pragma once
#include "../BufferInterface.h"

struct StaticStructuredBufferDescription;

//読み込み専用StructuredBuffer
class StaticStructuredBuffer final : public GPUBufferBehavior, IShaderBuffer
{

public:

	StaticStructuredBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	uint32_t OutProperSRVHeapIndex(int frameIndex_ = 0)const override;

private:


};

