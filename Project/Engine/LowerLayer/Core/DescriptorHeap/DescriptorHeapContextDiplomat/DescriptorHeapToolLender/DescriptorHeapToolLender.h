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
		ID3D12DescriptorHeap*	//srvUav。他のタイプがもし必要になったら考える
	> tools;

public:


	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Licence;

	ToolLender
	(
		NexusFieldProof proof_, 
		DescriptorHeapContext::ViewCreator& viewCretator_,
		DescriptorHeapPoolContainer& descriptorHeapPoolContainer_
	);
	
	///ツールの貸し出し
	template<typename ToolType>
	auto& Lend(typename CmdTypeTraits<ToolType>::Licence licence_)
	{
		return *std::get<ToolType*>(tools);
	}

};


template<>
struct DescriptorHeapContext::ToolLender::CmdTypeTraits<DescriptorHeapContext::ViewCreator>
{
	using Licence = BasicViewManagementLicence;
};

template<>
struct DescriptorHeapContext::ToolLender::CmdTypeTraits<ID3D12DescriptorHeap>
{
	using Licence = UsesSrvDescriptorHeapLicence;
};


