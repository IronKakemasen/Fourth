#pragma once
#include "../../BufferContext.h"

class BufferContext::ToolLender
{
	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct CmdTypeTraits;

	//バッファクリエイターやアップローダー、ディスパッチャーを触ってもいい資格
	struct BasicBufferManagementLicence;

	///貸し出せるツール
	std::tuple
	<
		BufferCreator*, 
		BufferUploader*, 
		BufferDispatcher*,
		BufferCollector*,
		GlobalConstantBuffers*
	> tools;


public:

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Type;

	ToolLender
	(
		NexusFieldProof proof_,
		BufferCreator* creator_,
		BufferUploader* uploader_,
		BufferDispatcher* dispatcher_,
		BufferCollector* collector_,
		GlobalConstantBuffers* worldConstantBuffers_
	);


	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(typename CmdTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}

};



template<>
struct BufferContext::ToolLender::CmdTypeTraits<BufferContext::BufferCreator>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::CmdTypeTraits<BufferContext::BufferUploader>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::CmdTypeTraits<BufferContext::BufferDispatcher>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::CmdTypeTraits<BufferContext::BufferCollector>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::CmdTypeTraits<BufferContext::GlobalConstantBuffers>
{
	using Type = BasicBufferManagementLicence;
};
