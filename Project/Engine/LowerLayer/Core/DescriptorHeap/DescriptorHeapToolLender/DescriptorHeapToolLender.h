#pragma once
#include "../DescriptorHeapContext.h"
#include "../../../Resource/Buffer/BufferContext.h"

class SwapChainContext;

class DescriptorHeapContext::ToolLender
{
	struct BasicViewManagementLicence;

public:

	ToolLender(InstanceKey key_, DescriptorHeapContext::ViewCreator* viewCretator_);
	
	template<typename ToolType>
	struct LicenceTypeTraits;

	template<>
	struct LicenceTypeTraits<DescriptorHeapContext::ViewCreator>
	{
		using Type = BasicViewManagementLicence;
	};

	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(LicenceTypeTraits<ToolType> licence_)
	{
		return std::get<ToolType*>(tools);
	}

private:

	std::tuple<ViewCreator*> tools;

};

struct DescriptorHeapContext::ToolLender::BasicViewManagementLicence
{
private:

	friend class SwapChainContext;
	friend class BufferContext::BufferAssembler;
	explicit BasicViewManagementLicence() = default;
};

