#pragma once
#include "../../BufferContext.h"

class BufferContext::ToolLender
{
	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct ToolTypeTraits;

	//バッファクリエイターやアップローダー、ディスパッチャーを触ってもいい資格
	struct BasicBufferManagementLicence;
	//定数バッファクラスを触ってもいい資格
	struct UsesGlobalConstantBuffersLicence;


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
	using LicenceType = typename ToolTypeTraits<ToolType>::Licence;

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
	auto* Lend(typename ToolTypeTraits<ToolType>::Licence licence_)
	{
		return std::get<ToolType*>(tools);
	}

};



template<>
struct BufferContext::ToolLender::ToolTypeTraits<BufferContext::BufferCreator>
{
	using Licence = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::ToolTypeTraits<BufferContext::BufferUploader>
{
	using Licence = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::ToolTypeTraits<BufferContext::BufferDispatcher>
{
	using Licence = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::ToolTypeTraits<BufferContext::BufferCollector>
{
	using Licence = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::ToolTypeTraits<BufferContext::GlobalConstantBuffers>
{
	using Licence = UsesGlobalConstantBuffersLicence;
};
