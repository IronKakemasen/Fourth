#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"



//定数バッファクラス
class ConstantBuffer : public GPUBufferBehavior
{
public:

	ConstantBuffer
	(
		const InstanceKey& instanceKey_,
		std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

};

