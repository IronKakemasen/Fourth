#pragma once
#include "../../DescriptorHeapContext.h"


class DescriptorHeapContext::ToolLender
{
	template<typename ToolType>
	struct CmdTypeTraits;

	struct BasicViewManagementLicence;
	struct UsesSrvDescriptorHeapLicence;

	//貸出可能なツール
	std::tuple
	<
		ViewCreator*,
		ID3D12DescriptorHeap*	//srvUav
	> tools;

public:


	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_, DescriptorHeapContext::ViewCreator* viewCretator_);
	
	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(typename CmdTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}

};


template<>
struct DescriptorHeapContext::ToolLender::CmdTypeTraits<DescriptorHeapContext::ViewCreator>
{
	using Type = BasicViewManagementLicence;
};

template<>
struct DescriptorHeapContext::ToolLender::CmdTypeTraits<ID3D12DescriptorHeap>
{
	using Type = UsesSrvDescriptorHeapLicence;
};


