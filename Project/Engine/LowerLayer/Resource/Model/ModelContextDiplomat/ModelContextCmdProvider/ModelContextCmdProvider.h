#pragma once
#include "../../ModelContext.h"
#include "../../ModelContextCmds.h"


class ModelContext::CommandProvider
{
	template<typename CmdType>
	struct CmdTypeTraits;
	

public:

	template<typename CmdType>
	using LicenceType = typename CmdTypeTraits<CmdType>::Type;

	CommandProvider
	(
		NexusFieldProof proof_
	);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename CmdTypeTraits<CmdType>::Type licence_);


private:


};


