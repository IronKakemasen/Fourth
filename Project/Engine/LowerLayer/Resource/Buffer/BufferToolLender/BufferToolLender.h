#pragma once
#include "../BufferContext.h"
#include "../../Mesh/MeshContext.h"

class BufferContext::ToolLender
{
public:

	//貸し出すツールのデータ型とそれに対応したLicenceのデータ型を結び付ける
	template<typename ToolType>
	struct LicenceTypeTraits;

	//ただのエイリアステンプレート
	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

private:
	//バッファクリエイターやアップローダーを触ってもいい資格
	struct BasicBufferManagementLicence;

	///貸し出せるツール
	std::tuple<BufferContext::BufferCreator*, BufferContext::BufferUploader*> tools;

public:

	ToolLender
	(
		BufferContext::InstanceKey key_,
		BufferContext::BufferCreator* creator_,
		BufferContext::BufferUploader* uploader_
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
