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
	struct ResourceUploaderAccessLicence;


	///貸し出せるツール
	std::tuple<ID3D12CommandQueue*, CommandContext::ResourceUploader*> tools;

public:

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender
	(
		NexusFieldProof proof_,
		ID3D12CommandQueue* cmdQueue_,
		CommandContext::ResourceUploader* resourceUploader_
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

struct CommandContext::ToolLender::ResourceUploaderAccessLicence
{
private:

	friend class Nexus;
	explicit ResourceUploaderAccessLicence() = default;
};


template<>
struct CommandContext::ToolLender::LicenceTypeTraits<ID3D12CommandQueue>
{
	using Type = CommandQueueAccessLicence;
};

template<>
struct CommandContext::ToolLender::LicenceTypeTraits<CommandContext::ResourceUploader>
{
	using Type = ResourceUploaderAccessLicence;
};
