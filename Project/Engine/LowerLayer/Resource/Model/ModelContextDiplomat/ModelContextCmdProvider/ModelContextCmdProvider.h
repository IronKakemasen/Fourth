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

	CommandProvider(NexusFieldProof proof_, ModelContainer* modelContainer_);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename CmdTypeTraits<CmdType>::Type licence_);


private:

	ModelContainer* modelContainer;

};

template<>
struct ModelContext::CommandProvider::CmdTypeTraits<ModelContextCmds::WatchModelContainer>
{
	using Type = WatchModelContainerLicence;
};



template<>
ModelContextCmds::WatchModelContainer ModelContext::CommandProvider::Provide<ModelContextCmds::WatchModelContainer>
(typename CmdTypeTraits<ModelContextCmds::WatchModelContainer>::Type licence_);

