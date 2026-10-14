#pragma once
#include "../../ModelContext.h"
#include "../../ModelContextCmds.h"


class ModelContext::CommandProvider
{
	template<typename CmdType>
	struct CmdTypeTraits;
	
	struct WatchModelContainerLicence;

public:

	template<typename CmdType>
	using LicenceType = typename CmdTypeTraits<CmdType>::Type;

	CommandProvider
	(
		NexusFieldProof proof_,
		ModelCreator& modelCreator_
	);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename CmdTypeTraits<CmdType>::Type licence_);


private:

	ModelCreator& modelCreator;
};


template<>
struct ModelContext::CommandProvider::CmdTypeTraits<ModelContextCmds::WatchAllModelsRenderStatePattern>
{
	using Type = WatchModelContainerLicence;
};



template<>
ModelContextCmds::WatchAllModelsRenderStatePattern ModelContext::CommandProvider::Provide<ModelContextCmds::WatchAllModelsRenderStatePattern>
(typename CmdTypeTraits<ModelContextCmds::WatchAllModelsRenderStatePattern>::Type licence_);
