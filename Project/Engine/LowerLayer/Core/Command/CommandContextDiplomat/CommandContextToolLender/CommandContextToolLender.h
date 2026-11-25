#pragma once
#include "../../CommandContext.h"


class CommandContext::ToolLender
{
	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct CmdTypeTraits;

	//CommandQueueを扱う資格
	struct AccessCommandQueueLicence;
	//RuntimeCmdWrapperをしようする資格
	struct UsesRuntimeCmdWrapperLicence;
	////CommandListを扱う資格
	struct AccessCommandListLicence;

	///貸し出せるツール
	std::tuple
	<
		ID3D12CommandQueue*,
		RuntimeWrapper*,
		ID3D12GraphicsCommandList6*
	> tools;

public:

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Licence;

	ToolLender
	(
		NexusFieldProof proof_,
		ID3D12CommandQueue& cmdQueue_,
		ID3D12GraphicsCommandList6& cmdList_,
		RuntimeWrapper& runtimeWrapper_
	);


	///ツールの貸し出し
	template<typename ToolType>
	auto& Lend(typename CmdTypeTraits<ToolType>::Licence licence_)
	{
		return *std::get<ToolType*>(tools);
	}

};


template<>
struct CommandContext::ToolLender::CmdTypeTraits<ID3D12CommandQueue>
{
	using Licence = AccessCommandQueueLicence;
};

template<>
struct CommandContext::ToolLender::CmdTypeTraits<RuntimeWrapper>
{
	using Licence = UsesRuntimeCmdWrapperLicence;
};

template<>
struct CommandContext::ToolLender::CmdTypeTraits<ID3D12GraphicsCommandList6>
{
	using Licence = AccessCommandListLicence;
};



