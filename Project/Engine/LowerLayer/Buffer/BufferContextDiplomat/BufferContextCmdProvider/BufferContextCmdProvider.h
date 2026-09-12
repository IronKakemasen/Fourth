#pragma once
#include "../../BufferContext.h"
#include "../../BufferContextCmds.h"


class BufferContext::CmdProvider
{
	template<typename CmdType>
	struct CmdTypeTraits;

	struct UsesCBufferCreatorLicence;

public:

	template<typename CmdType>
	using LicenceType = typename CmdTypeTraits<CmdType>::Type;

	CmdProvider(NexusFieldProof proof_, GlobalConstantBufferCreator* cBufferCreator_);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename CmdTypeTraits<CmdType>::Type licence_);

private:

	GlobalConstantBufferCreator* cBufferCreator;
};

template<>
struct BufferContext::CmdProvider::CmdTypeTraits<BufferContextCmds::CreateCBufferCmd>
{
	using Type = UsesCBufferCreatorLicence;
};


template<>
BufferContextCmds::CreateCBufferCmd BufferContext::CmdProvider::Provide
(typename CmdTypeTraits<BufferContextCmds::CreateCBufferCmd>::Type licence_);
