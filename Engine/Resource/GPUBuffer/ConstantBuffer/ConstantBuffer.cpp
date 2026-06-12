#include "PreCompileHedder.h"
#include "ConstantBuffer.h"
#include "../../BufferDescriptions/IBufferDescription.h"


ConstantBuffer::ConstantBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
	std::unique_ptr <IBufferDescription>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_), std::move(description_))
{

}