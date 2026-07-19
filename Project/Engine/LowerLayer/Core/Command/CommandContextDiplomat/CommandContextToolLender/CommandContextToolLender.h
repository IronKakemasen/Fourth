#pragma once
#include "../../CommandContext.h"

class SwapChainContext;

class CommandContext::ToolLender
{
	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct LicenceTypeTraits;

	//CommandQueueを扱う資格
	struct CommandQueueAccessLicence;

	///貸し出せるツール
	std::tuple<ID3D12CommandQueue*> tools;

public:

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender
	(
		CommandContext::InstanceKey key_,
		ID3D12CommandQueue* cmdQueue_
	);


	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}


};


struct CommandContext::ToolLender::CommandQueueAccessLicence
{
private:

	friend class SwapChainContext;
	explicit CommandQueueAccessLicence() = default;
};


template<>
struct CommandContext::ToolLender::LicenceTypeTraits<ID3D12CommandQueue>
{
	using Type = CommandQueueAccessLicence;
};
