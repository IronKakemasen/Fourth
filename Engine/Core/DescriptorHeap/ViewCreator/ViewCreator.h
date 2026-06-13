#pragma once
#include "../DescriptorHeapContext.h"
#include "../DescriptorHeapClass/DescriptorHeapClass.h"
#include <type_traits> 

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
		DescriptorHeapContext::CreateKey createKey_,
		DescriptorHeapClass* RTVdescriptorHeapClass_,
		DescriptorHeapClass* SRVUAVdescriptorHeapClass_,
		DescriptorHeapClass* DSVdescriptorHeapClass_,
		DescriptorHeapContext::CreateRTVCommand rtvCmd_,
		DescriptorHeapContext::CreateSRVCommand srvCmd_,
		DescriptorHeapContext::CreateDSVCommand dsvCmd_,
		DescriptorHeapContext::CreateUAVCommand uavCmd_
	);

	//VIEWを生成し、インデックスまたはハンドルを返す。
	template<typename Index , typename ViewType>
	Index CreateView(ID3D12Resource* resource_, const ViewType& viewDesc)
	{
		//ViewTypeどのヒープを使うべきか分岐
		HeapType type;
		if constexpr (std::is_same_v<ViewType, D3D12_RENDER_TARGET_VIEW_DESC>) { type = kRTV; }
		else if constexpr (std::is_same_v<ViewType, D3D12_DEPTH_STENCIL_VIEW_DESC>) { type = kDSV; }
		else { type = kSRVUAV; }

		//ヒープを取り出す
		auto* targetHeap = descriptorHeap_map[type];

		Index allocateIndex = targetHeap->WatchAllocateIndex<Index>();

		//view生成数に応じたCPUハンドルを取得し、その後ヒープ側のカウンタを進める
		auto handleCPU = targetHeap->CalculateHandleThenIncrement<D3D12_CPU_DESCRIPTOR_HANDLE>(DescriptorHeapClass::AccessKey{});

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
			uavCmd(resource_, &viewDesc, handleCPU, nullptr);
		}

		//uintまたはCPUのインデックスを返す
		return allocateIndex;
	}
};
















