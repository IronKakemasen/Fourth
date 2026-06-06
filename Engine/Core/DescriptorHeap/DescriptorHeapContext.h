#pragma once


class DescriptorHeapContext
{
public:

	struct InstanceKey;
	
	DescriptorHeapContext(InstanceKey instanceKey_);
	~DescriptorHeapContext();

	class DescriptorHeapCreator;


};


//生成できるのはWinAppのみ
struct DescriptorHeapContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};


[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ID3D12Device* device_,
	D3D12_DESCRIPTOR_HEAP_TYPE heapType_, UINT numDescriptors_, bool shaderVisible);