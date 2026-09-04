#pragma once
#include "../../DescriptorHeapContext.h"
#include "../../../../Resource/Buffer/BufferContext.h"

class SwapChainContext;

class DescriptorHeapContext::ToolLender
{
	template<typename ToolType>
	struct CmdTypeTraits;

	struct BasicViewManagementLicence;

	//貸出可能なツール
	std::tuple<ViewCreator*> tools;

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

struct DescriptorHeapContext::ToolLender::BasicViewManagementLicence
{
private:

	friend class SwapChainContext;
	friend class BufferContext::BufferAssembler;
	explicit BasicViewManagementLicence() = default;
};

template<>
struct DescriptorHeapContext::ToolLender::CmdTypeTraits<DescriptorHeapContext::ViewCreator>
{
	using Type = BasicViewManagementLicence;
};
