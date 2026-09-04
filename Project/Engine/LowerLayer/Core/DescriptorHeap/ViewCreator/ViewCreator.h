#pragma once
#include "../DescriptorHeapPoolContainer/DescriptorHeapPoolContainer.h"
#include "../../../Core/Device/DeviceContextCmds.h"

class GPUBufferBehavior;

class DescriptorHeapContext::ViewCreator
{
	enum class HeapType
	{
		kRTV,
		kSRVUAV,
		kDSV

		,kCount
	};

	//DescriptorHeapPoolのアドレス
	std::array < DescriptorHeapPool*, UINT(HeapType::kCount) > descriptorHeapPoolArray;

	//コマンド
	DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC> rtvCmd;
	DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC> srvCmd;
	DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC> dsvCmd;
	DeviceContextCmds::CreateUAV uavCmd;

	template<typename ViewDescType>
	struct DescTypeTraits;

	template<typename ViewDescType>
	using DescType = typename DescTypeTraits<ViewDescType>::Type;

public:
	ViewCreator
	(
		NexusFieldProof proof_,
		DescriptorHeapPoolContainer& descriptorHeapPoolContainer_,
		DeviceContextDiplomat& deviceContextDiplomat_
	);

	///VIEWを生成し、インデックスやハンドルを返す。
	template<typename ViewDescType>
	std::tuple<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> CreateView(ID3D12Resource* resource_, const ViewDescType* viewDesc, ID3D12Resource* counterResource_ = nullptr)
	{
		//ViewTypeどのヒープを使うべきか分岐
		constexpr HeapType type = DescTypeTraits<ViewDescType>::heapType;
		//ディスクリプタヒープを取り出す
		DescriptorHeapPool* targetHeap = descriptorHeapPoolArray.at((UINT)type);

		//空きヒープインデックスを割り当てる
		auto[allocateIndex, handleCPU, handleGPU] = targetHeap->DistributeFreeHeapIndex(DescriptorHeapPool::CreateViewKey{});

		//ビュー生成
		if constexpr (std::is_same_v<ViewDescType, D3D12_RENDER_TARGET_VIEW_DESC>)
		{
			rtvCmd(resource_, viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewDescType, D3D12_SHADER_RESOURCE_VIEW_DESC>)
		{
			srvCmd(resource_, viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewDescType, D3D12_DEPTH_STENCIL_VIEW_DESC>)
		{
			dsvCmd(resource_, viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewDescType, D3D12_UNORDERED_ACCESS_VIEW_DESC>)
		{
			uavCmd(resource_, viewDesc, handleCPU, counterResource_);
		}

		Log<DescTypeTraits<ViewDescType>::heapType>(allocateIndex);

		//uint、CPU・GPUのインデックスを返す
		return std::make_tuple(allocateIndex, handleCPU, handleGPU);
	}

private:

	template<HeapType heapType>
	void Log(const uint32_t handle_)const;
};


template<>
struct DescriptorHeapContext::ViewCreator::DescTypeTraits<D3D12_RENDER_TARGET_VIEW_DESC>
{
	static constexpr HeapType heapType = HeapType::kRTV;
};

template<>
struct DescriptorHeapContext::ViewCreator::DescTypeTraits<D3D12_SHADER_RESOURCE_VIEW_DESC>
{
	static constexpr HeapType heapType = HeapType::kSRVUAV;
};

template<>
struct DescriptorHeapContext::ViewCreator::DescTypeTraits<D3D12_UNORDERED_ACCESS_VIEW_DESC>
{
	static constexpr HeapType heapType = HeapType::kSRVUAV;
};

template<>
struct DescriptorHeapContext::ViewCreator::DescTypeTraits<D3D12_DEPTH_STENCIL_VIEW_DESC>
{
	static constexpr HeapType heapType = HeapType::kDSV;
};











