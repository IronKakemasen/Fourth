#pragma once
#include "../../CommandContext.h"


class CommandContext::ToolLender
{
	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct CmdTypeTraits;

	//CommandQueueを扱う資格
	struct AccessCommandQueueLicence;

	///貸し出せるツール
	std::tuple<ID3D12CommandQueue*> tools;

public:

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Type;

	ToolLender
	(
		NexusFieldProof proof_,
		ID3D12CommandQueue* cmdQueue_
	);


	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(typename CmdTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}

};


template<>
struct CommandContext::ToolLender::CmdTypeTraits<ID3D12CommandQueue>
{
	using Type = AccessCommandQueueLicence;
};

