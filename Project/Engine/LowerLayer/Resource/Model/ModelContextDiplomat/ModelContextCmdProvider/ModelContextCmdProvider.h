#pragma once
#include "../../ModelContext.h"
#include "../../ModelContextCmds.h"



using namespace ModelContextCmds;

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
struct ModelContext::CommandProvider::CmdTypeTraits<WatchModelContainer>
{
	using Type = WatchModelContainerLicence;
};

template<>
struct ModelContext::CommandProvider::CmdTypeTraits<WatchSeparatedModelContainer>
{
	using Type = WatchModelContainerLicence;
};


template<>
WatchModelContainer ModelContext::CommandProvider::Provide<WatchModelContainer>
(typename CmdTypeTraits<WatchModelContainer>::Type licence_);

template<>
WatchSeparatedModelContainer ModelContext::CommandProvider::Provide<WatchSeparatedModelContainer>
(typename CmdTypeTraits<WatchModelContainer>::Type licence_);

