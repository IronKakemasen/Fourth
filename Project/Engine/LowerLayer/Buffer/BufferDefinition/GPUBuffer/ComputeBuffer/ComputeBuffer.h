#pragma once
#include "../GPUBufferBehavior.h"
#include "../BufferInterface.h"


//読み書き
class ComputeBuffer final : public GPUBufferBehavior
{

public:

	ComputeBuffer
	(
		const InstanceKey& instanceKey_, 
		std::string const& name_,
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
		const BufferDescriptionBehavior& description_
	);


	///+/////////////////////////////////////////////////////////////
	///+/////////////////////////////////////////////////////////////
	///+抽象化予定

	///+/////////////////////////////////////////////////////////////
	///+/////////////////////////////////////////////////////////////

private:


};

