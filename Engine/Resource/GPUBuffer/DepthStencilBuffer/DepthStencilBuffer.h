#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"


//定数バッファクラス
class DepthStencilBuffer : public GPUBufferBehavior
{
public:

	DepthStencilBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	float WatchClearColor(ExtracteMaterialKey key_);
};

