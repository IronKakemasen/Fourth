#pragma once
#include "../BufferInterface.h"


//読み書き
class ComputeBuffer final : public GPUBufferBehavior
{

public:

	ComputeBuffer
	(
		const InstanceKey& instanceKey_, 
		std::string name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		const BufferDescriptionBehavior& description_
	);


	///+/////////////////////////////////////////////////////////////
	///+/////////////////////////////////////////////////////////////
	///+抽象化予定

	///+/////////////////////////////////////////////////////////////
	///+/////////////////////////////////////////////////////////////

	//virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
	//	CreateNextStepBarriers(ExtractMaterialKey key_) override;

private:


};

