#include "PreCompileHedder.h"
#include "ColorBuffer.h"


ColorBuffer::ColorBuffer(const InstanceKey& instanceKey_, std::string name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, ColorBufferDescription desc_) :
	GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_)), desc(desc_)
{


}