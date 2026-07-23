#pragma once
#include "../../BufferContext.h"
#include "../../../Mesh/MeshContext.h"

class BufferContext::ToolLender
{
	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct LicenceTypeTraits;

	//バッファクリエイターやアップローダー、ディスパッチャーを触ってもいい資格
	struct BasicBufferManagementLicence;

	///貸し出せるツール
	std::tuple
	<
		BufferContext::BufferCreator*, 
		BufferContext::BufferUploader*, 
		BufferContext::BufferDispatcher*,
		BufferContext::BufferCollector*
	> tools;


public:

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender
	(
		BufferContext::NexusFieldProof proof_,
		BufferContext::BufferCreator* creator_,
		BufferContext::BufferUploader* uploader_,
		BufferContext::BufferDispatcher* dispatcher_,
		BufferContext::BufferCollector * collector_
	);


	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}

};


struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class MeshContext::ModelDataCreator;
	explicit BasicBufferManagementLicence() = default;
};


template<>
struct BufferContext::ToolLender::LicenceTypeTraits<BufferContext::BufferCreator>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::LicenceTypeTraits<BufferContext::BufferUploader>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::LicenceTypeTraits<BufferContext::BufferDispatcher>
{
	using Type = BasicBufferManagementLicence;
};

template<>
struct BufferContext::ToolLender::LicenceTypeTraits<BufferContext::BufferCollector>
{
	using Type = BasicBufferManagementLicence;
};
