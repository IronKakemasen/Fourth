#pragma once
#include "../BufferContext.h"


class BufferContext::WorldConstantBuffers
{
public:

	struct Local_ImportLicence;

	using DoubleVirtualGPUAddress = std::array
		<D3D12_GPU_VIRTUAL_ADDRESS, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer>;

	WorldConstantBuffers
	(
		NexusFieldProof proof_
	);

	//ランタイム用のベクターコンテナに詰め変える(全てのコンスタントバッファの生成が終わった後)
	void PackRuntimeContainer(NexusFieldProof proof_, AgentKey agentKey_);
	//データの転送は一括で行いたいから、いつでもgpuVirtualAddressを見せれるように
	const std::vector<D3D12_GPU_VIRTUAL_ADDRESS>& WatchGPUAddressContainer(UINT curFrameIndex_)const
	{
		return gpuVirtualAddressVector[curFrameIndex_];
	}

	void Import
	(
		Local_ImportLicence licence_,
		std::string const bufferName_,
		const uint8_t bindSlot_ , 
		DoubleVirtualGPUAddress doubleVirtualGPUAddress_
	);

private:

	//一時保管用
	std::map<uint8_t, DoubleVirtualGPUAddress> gpuVirtualAddressMap;
	//デバッグ用
	std::map<uint8_t, std::string> bufferNameMap;

	//ランタイムで速度を稼ぎたいのでベクター版を用意
	std::array<std::vector<D3D12_GPU_VIRTUAL_ADDRESS>, (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer>
		gpuVirtualAddressVector;

};


struct BufferContext::WorldConstantBuffers::Local_ImportLicence
{
private:

	friend class ConstantBufferCreator;
	explicit Local_ImportLicence() = default;
};



