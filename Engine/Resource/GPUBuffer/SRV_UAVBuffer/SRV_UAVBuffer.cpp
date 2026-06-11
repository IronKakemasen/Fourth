#include "PreCompileHedder.h"
#include "SRV_UAVBuffer.h"


SRV_UAVBuffer::SRV_UAVBuffer(const InstanceKey& instanceKey_, std::string name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, SRV_UAVBufferDescription desc_) :
	GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_)), desc(desc_)
{

}

template<>
void SRV_UAVBuffer::OverrideIndex<ViewType::kSRV>(OverrideIndexKey key_, uint32_t index_)
{
	srvHeapIndex = index_;
}

template<>
void SRV_UAVBuffer::OverrideIndex<ViewType::kRTV>(OverrideIndexKey key_, uint32_t index_)
{
	uavHeapIndex = index_;
}


template void SRV_UAVBuffer::OverrideIndex<ViewType::kRTV>(OverrideIndexKey key_, uint32_t index_);
template void SRV_UAVBuffer::OverrideIndex<ViewType::kSRV>(OverrideIndexKey key_, uint32_t index_);
