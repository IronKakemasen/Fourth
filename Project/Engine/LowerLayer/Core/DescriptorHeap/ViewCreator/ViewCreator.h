#pragma once
#include "../DescriptorHeapContext.h"
#include "../DescriptorHeapPool/DescriptorHeapPool.h"

class GPUBufferBehavior;

class DescriptorHeapContext::ViewCreator
{
	enum HeapType
	{
		kRTV,
		kSRVUAV,
		kDSV
	};

	//DescriptorHeapPoolのアドレス
	std::unordered_map<HeapType, DescriptorHeapPool*> DescriptorHeapPool_Library;

	//コマンド
	DescriptorHeapContext::CreateRTVCommand rtvCmd;
	DescriptorHeapContext::CreateSRVCommand srvCmd;
	DescriptorHeapContext::CreateDSVCommand dsvCmd;
	DescriptorHeapContext::CreateUAVCommand uavCmd;

public:
	ViewCreator
	(
		DescriptorHeapContext::InstanceKey instanceKey_,
		DescriptorHeapPool* RTVdescriptorHeapPool_,
		DescriptorHeapPool* SRVUAVdescriptorHeapPool_,
		DescriptorHeapPool* DSVdescriptorHeapPool_,
		DescriptorHeapContext::CreateRTVCommand rtvCmd_,
		DescriptorHeapContext::CreateSRVCommand srvCmd_,
		DescriptorHeapContext::CreateDSVCommand dsvCmd_,
		DescriptorHeapContext::CreateUAVCommand uavCmd_
	);

	//VIEWを生成し、インデックスやハンドルを返す。
	template<typename ViewType>
	std::tuple<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> CreateView(ID3D12Resource* resource_, const ViewType* viewDesc, ID3D12Resource* counterResource_ = nullptr)
	{
		//ViewTypeどのヒープを使うべきか分岐
		HeapType type;
		if constexpr (std::is_same_v<ViewType, D3D12_RENDER_TARGET_VIEW_DESC>) { type = kRTV; }
		else if constexpr (std::is_same_v<ViewType, D3D12_DEPTH_STENCIL_VIEW_DESC>) { type = kDSV; }
		else { type = kSRVUAV; }

		//ディスクリプタヒープを取り出す
		auto* targetHeap = DescriptorHeapPool_Library.at(type);

		//空きヒープインデックスを割り当てる
		auto[allocateIndex, handleCPU, handleGPU] = targetHeap->ProvideFreeHeapIndex(DescriptorHeapPool::CreateViewKey{});

		//ビュー生成
		if constexpr (std::is_same_v<ViewType, D3D12_RENDER_TARGET_VIEW_DESC>)
		{
			rtvCmd(resource_, viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewType, D3D12_SHADER_RESOURCE_VIEW_DESC>)
		{
			srvCmd(resource_, viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewType, D3D12_DEPTH_STENCIL_VIEW_DESC>)
		{
			dsvCmd(resource_, viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewType, D3D12_UNORDERED_ACCESS_VIEW_DESC>)
		{
			uavCmd(resource_, viewDesc, handleCPU, counterResource_);
		}

		//uint、CPU・GPUのインデックスを返す
		return std::make_tuple(allocateIndex, handleCPU, handleGPU);
	}
};
















