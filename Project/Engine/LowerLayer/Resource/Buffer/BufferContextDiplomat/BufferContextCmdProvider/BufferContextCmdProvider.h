#pragma once
#include "../../BufferContext.h"
#include "../../BufferContextCmds.h"


class BufferContext::CmdProvider
{
	template<typename CmdType>
	struct LicenceTypeTraits;

	struct UsesCBufferCreatorLicence;

public:

	template<typename CmdType>
	using LicenceType = typename LicenceTypeTraits<CmdType>::Type;

	CmdProvider(NexusFieldProof proof_, ConstantBufferCreator* cBufferCreator_);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename LicenceTypeTraits<CmdType>::Type licence_);

private:

	ConstantBufferCreator* cBufferCreator;
};

template<>
struct BufferContext::CmdProvider::LicenceTypeTraits<BufferContextCmds::CreateCBufferCmd>
{
	using Type = UsesCBufferCreatorLicence;
};


template<>
BufferContextCmds::CreateCBufferCmd BufferContext::CmdProvider::Provide
(typename LicenceTypeTraits<BufferContextCmds::CreateCBufferCmd>::Type licence_);
