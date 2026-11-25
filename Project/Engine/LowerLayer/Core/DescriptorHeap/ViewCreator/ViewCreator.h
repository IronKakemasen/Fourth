#pragma once
#include "../DescriptorHeapPoolContainer/DescriptorHeapPoolContainer.h"
#include "../../../Core/Device/DeviceContextCmds.h"

class GPUBufferBehavior;

class DescriptorHeapContext::ViewCreator
{
public:

	enum class HeapType
	{
		kRTV,
		kSRVUAV,
		kDSV

		, kCount
	};

	//srvDescriptorHeapの予約済みスロット
	enum class ReservedSrvIndex
	{
		kImGui,

		kCount
	};

	enum class ReservedDsvIndex
	{
		kCount
	};

	enum class ReservedRtvIndex
	{
		kCount
	};

private:

	struct HeapHandles
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cpu;
		D3D12_GPU_DESCRIPTOR_HANDLE gpu;
	};

	template<typename ViewDescType>
	struct DescTypeTraits;

	template<HeapType heapType>
	struct HeapTypeTraits;

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
		DescriptorHeapPool* targetHeap = AccessHeapPool<type>();

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

	//予約したディスクリプタヒープの特定スロットのハンドルを見る
	template<HeapType heapType>
	HeapHandles const& WatchReservedHeapHandles(UINT slot_)const
	{
		return reservedHeapIndicesArr.at(UINT(heapType))[slot_];
	}

private:

	template<HeapType heapType>
	auto* AccessHeapPool()
	{
		//ディスクリプタヒープを取り出す
		return descriptorHeapPoolArray.at((UINT)heapType);
	}

	template<HeapType heapType>
	void Log(const uint32_t handle_)const;

	template<HeapType heapType>
	void ReserveHeapSlot();

	//DescriptorHeapPoolのアドレス
	std::array<DescriptorHeapPool*, UINT(HeapType::kCount)> descriptorHeapPoolArray;

	//ビュークリエイターを通してビューを作らない、
	//他機構(imGuiなど)が予約したDescriptorHeapのハンドルデータ
	std::array<std::vector<HeapHandles>, UINT(HeapType::kCount)> reservedHeapIndicesArr;

	//コマンド
	DeviceContextCmds::CreateView<D3D12_RENDER_TARGET_VIEW_DESC> rtvCmd;
	DeviceContextCmds::CreateView<D3D12_SHADER_RESOURCE_VIEW_DESC> srvCmd;
	DeviceContextCmds::CreateView<D3D12_DEPTH_STENCIL_VIEW_DESC> dsvCmd;
	DeviceContextCmds::CreateUAV uavCmd;
};

template<>
struct DescriptorHeapContext::ViewCreator::HeapTypeTraits < DescriptorHeapContext::ViewCreator::HeapType::kRTV>
{
	static constexpr UINT kReservedHeapSize = (UINT)ReservedRtvIndex::kCount;
};

template<>
struct DescriptorHeapContext::ViewCreator::HeapTypeTraits < DescriptorHeapContext::ViewCreator::HeapType::kSRVUAV>
{
	static constexpr UINT kReservedHeapSize = (UINT)ReservedSrvIndex::kCount;
};

template<>
struct DescriptorHeapContext::ViewCreator::HeapTypeTraits < DescriptorHeapContext::ViewCreator::HeapType::kDSV>
{
	static constexpr UINT kReservedHeapSize = (UINT)ReservedDsvIndex::kCount;
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











