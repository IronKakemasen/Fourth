#include "RootSignatureContext.h"
#include "RootSignatureLibrary/RootSignatureLibrary.h"
#include "RootSignatureCreator/RootSignatureCreator.h"
#include "RootSignatureCreator/RootSignatureAssembler/RootSignatureAssembler.h"
#include "RootSignatureContextDiplomat/RootSignatureContextDiplomat.h"
#include "RootSignatureContextDiplomat/RootSignatureToolLender/RootSignatureToolLender.h"

namespace
{
	auto const fileName = "RootSignatureContext.cpp";
}

RootSignatureContext::RootSignatureContext(NexusFieldProof proof_, DeviceContextDiplomat* deviceContextDiplomat_)
{
	Logger::Entry("RootSignatureContext: Constructor");

	rootSignatureLibrary.reset(new RootSignatureLibrary(proof_));
	Logger::Log("Instantiate: rootSignatureLibrary", fileName);

	rootSignatureCreator.reset
	(
		new RootSignatureCreator
		(
			proof_,
			std::make_unique<Assembler>(proof_, deviceContextDiplomat_),
			rootSignatureLibrary.get()
		)
	);

	Logger::Log("Instantiate: RootSignatureAssembler", fileName);
	Logger::Log("Instantiate: RootSignatureCreator", fileName);


	diplomat.reset
	(
		new RootSignatureContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, rootSignatureCreator.get())
		)
	);
	Logger::Log("Instantiate: ToolLender", fileName);
	Logger::Log("Instantiate: Diplomat", fileName);


	Logger::End("RootSignatureContext: Constructor");
}

RootSignatureContext::~RootSignatureContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////