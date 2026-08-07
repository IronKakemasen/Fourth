#pragma once
#include "../../ModelContext.h"
#include "ModelContextCmds.h"


class ModelContext::CommandProvider
{
	template<typename CmdType>
	struct LicenceTypeTraits;
	
	struct WatchModelContainerLicence;

public:

	template<typename CmdType>
	using LicenceType = typename LicenceTypeTraits<CmdType>::Type;

	CommandProvider(NexusFieldProof proof_, ModelContainer* modelContainer_);

	
	template<typename CmdType>
	CmdType Provide(typename LicenceTypeTraits<CmdType>::Type type_);


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
(typename LicenceTypeTraits<ModelContextCmds::WatchModelContainer>::Type type_);

