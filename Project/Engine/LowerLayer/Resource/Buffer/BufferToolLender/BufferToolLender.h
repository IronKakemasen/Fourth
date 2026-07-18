#pragma once
#include "../BufferContext.h"
#include "../../Mesh/MeshContext.h"

class BufferContext::ToolLender
{
	//バッファクリエイターやアップローダーを触ってもいい資格
	struct BasicBufferManagementLicence;

public:

	ToolLender
	(
		BufferContext::InstanceKey key_,
		BufferContext::BufferCreator* creator_,
		BufferContext::BufferUploader* uploader_
	);

	template<typename ToolType>
	struct LicenceTypeTraits;

	template<>
	struct LicenceTypeTraits<BufferContext::BufferCreator>
	{
		using Type = BasicBufferManagementLicence;
	};

	template<>
	struct LicenceTypeTraits<BufferContext::BufferUploader>
	{
		using Type = BasicBufferManagementLicence;
	};

	///ツールの貸し出し
	template<typename ToolType>
	auto* Lend(LicenceTypeTraits<ToolType> licence_)
	{
		return std::get<ToolType*>(tools);
	}

private:

	std::tuple<BufferContext::BufferCreator*, BufferContext::BufferUploader*> tools;
};


struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class MeshContext::ModelDataCreator;
	explicit BasicBufferManagementLicence() = default;
};



