#pragma once
#include "../DescriptorHeapContext.h"
#include "../../../Resource/Buffer/BufferContext.h"

class SwapChainContext;

class DescriptorHeapContext::ToolLender
{
public:

	template<typename ToolType>
	struct LicenceTypeTraits;

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

private:

	struct BasicViewManagementLicence;

	//貸出可能なツール
	std::tuple<ViewCreator*> tools;

public:

	ToolLender(InstanceKey key_, DescriptorHeapContext::ViewCreator* viewCretator_);
	
	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type licence_)
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
struct DescriptorHeapContext::ToolLender::LicenceTypeTraits<DescriptorHeapContext::ViewCreator>
{
	using Type = BasicViewManagementLicence;
};
