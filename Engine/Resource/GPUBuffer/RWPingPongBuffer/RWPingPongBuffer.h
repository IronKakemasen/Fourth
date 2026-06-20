#pragma once
#include "../GPUBufferBehavior.h"
#include "../../BufferDescriptions/RWPingPongBufferDescription/RWPingPongBufferDescription.h"


//読み書き
class RWPingPongBuffer final : public GPUBufferBehavior
{
	enum Status
	{
		kSRV_UAV,	//index0が読み込み用、index1が書き込み用
		kUAV_SRV	//その逆
	};

public:

	RWPingPongBuffer
	(
		const InstanceKey& instanceKey_, 
		std::string name_,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, 
		Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, 
		std::unique_ptr <BufferDescriptionBehavior>&& description_
	);

	uint32_t CurrentSRVHeapIndex();
	uint32_t CurrentUAVHeapIndex();

	virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
		CreateNextStepBarriers(ExtractMaterialKey key_)override;

private:

	Status status = kSRV_UAV;
	void Swap();

};

