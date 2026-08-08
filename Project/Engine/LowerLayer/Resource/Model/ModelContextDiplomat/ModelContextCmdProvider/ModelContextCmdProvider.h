#pragma once
#include "../../ModelContext.h"
#include "../../ModelContextCmds.h"


class ModelContext::CommandProvider
{
	template<typename CmdType>
	struct LicenceTypeTraits;
	
	struct WatchModelContainerLicence;

public:

	template<typename CmdType>
	using LicenceType = typename LicenceTypeTraits<CmdType>::Type;

	CommandProvider(NexusFieldProof proof_, ModelContainer* modelContainer_);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename LicenceTypeTraits<CmdType>::Type licence_);


private:

	ModelContainer* modelContainer;

};

template<>
struct ModelContext::CommandProvider::LicenceTypeTraits<ModelContextCmds::WatchModelContainer>
{
	using Type = WatchModelContainerLicence;
};



template<>
ModelContextCmds::WatchModelContainer ModelContext::CommandProvider::Provide<ModelContextCmds::WatchModelContainer>
(typename LicenceTypeTraits<ModelContextCmds::WatchModelContainer>::Type licence_);

