#pragma once
#include "../BufferInterface.h"



//定数バッファクラス
class ConstantBuffer final : public GPUBufferBehavior
{
public:

	ConstantBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

};

