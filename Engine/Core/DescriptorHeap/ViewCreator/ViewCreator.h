#pragma once
#include "../DescriptorHeapContext.h"
#include "../DescriptorHeapClass/DescriptorHeapClass.h"

class GPUBufferBehavior;

class ViewCreator
{
	enum HeapType
	{
		kRTV,
		kSRVUAV,
		kDSV
	};

	//DescriptorHeapClassのアドレス
	std::unordered_map<HeapType, DescriptorHeapClass*> descriptorHeap_map;

	//コマンド
	DescriptorHeapContext::CreateRTVCommand rtvCmd;
	DescriptorHeapContext::CreateSRVCommand srvCmd;
	DescriptorHeapContext::CreateDSVCommand dsvCmd;
	DescriptorHeapContext::CreateUAVCommand uavCmd;

public:
	ViewCreator
	(
		DescriptorHeapContext::InstanceKey instanceKey_,
		DescriptorHeapClass* RTVdescriptorHeapClass_,
		DescriptorHeapClass* SRVUAVdescriptorHeapClass_,
		DescriptorHeapClass* DSVdescriptorHeapClass_,
		DescriptorHeapContext::CreateRTVCommand rtvCmd_,
		DescriptorHeapContext::CreateSRVCommand srvCmd_,
		DescriptorHeapContext::CreateDSVCommand dsvCmd_,
		DescriptorHeapContext::CreateUAVCommand uavCmd_
	);

	//VIEWを生成し、インデックスまたはハンドルを返す。
	template<typename ViewType>
	std::tuple<uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> CreateView(ID3D12Resource* resource_, const ViewType& viewDesc, ID3D12Resource* counterResource_ = nullptr)
	{
		//ViewTypeどのヒープを使うべきか分岐
		HeapType type;
		if constexpr (std::is_same_v<ViewType, D3D12_RENDER_TARGET_VIEW_DESC>) { type = kRTV; }
		else if constexpr (std::is_same_v<ViewType, D3D12_DEPTH_STENCIL_VIEW_DESC>) { type = kDSV; }
		else { type = kSRVUAV; }

		//ヒープを取り出す
		auto* targetHeap = descriptorHeap_map[type];

		//view生成数に応じたハンドルを取得
		uint32_t allocateIndex = targetHeap->GetHandle<uint32_t>();
		auto handleCPU = targetHeap->GetHandle<D3D12_CPU_DESCRIPTOR_HANDLE>();
		auto handleGPU = targetHeap->GetHandle<D3D12_GPU_DESCRIPTOR_HANDLE>();

		//ビュー生成
		if constexpr (std::is_same_v<ViewType, D3D12_RENDER_TARGET_VIEW_DESC>)
		{
			rtvCmd(resource_, &viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewType, D3D12_SHADER_RESOURCE_VIEW_DESC>)
		{
			srvCmd(resource_, &viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewType, D3D12_DEPTH_STENCIL_VIEW_DESC>)
		{
			dsvCmd(resource_, &viewDesc, handleCPU);
		}
		else if constexpr (std::is_same_v<ViewType, D3D12_UNORDERED_ACCESS_VIEW_DESC>)
		{
			uavCmd(resource_, &viewDesc, handleCPU, counterResource_);
		}

		//ビュー生成数をインクリメント
		targetHeap->Increment(DescriptorHeapClass::AccessKey{});


		//uint、CPU・GPUのインデックスを返す
		return std::make_tuple(allocateIndex, handleCPU, handleGPU);
	}
};
















