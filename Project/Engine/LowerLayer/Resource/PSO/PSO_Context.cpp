#include "PSO_Context.h"
#include "PSO_Creator/PSO_Assembler/PSO_Assembler.h"
#include "PSO_Creator/PSO_Creator.h"
#include "PSO_Container/PSO_Container.h"

#include "PSO_ContextDiplomat/PSO_ContextDiplomat.h"
#include "PSO_ContextDiplomat/PSO_ContextToolLender/PSO_ContextToolLender.h"

namespace
{
	auto const fileName = "PSO_Context.cpp";
}


PSO_Context::PSO_Context
(
	NexusFieldProof proof_,
	DeviceContextDiplomat* deviceContextDiplomat_
)
{
	Logger::Entry("PSO_Context: Constructor");
	
	psoContainer.reset(new PSO_Container(proof_));
	Logger::Log("Instantiate: PSO_Container", fileName);

	psoCreator.reset
	(
		new PSO_Creator
		(
			proof_,
			std::make_unique<Assembler>(proof_, deviceContextDiplomat_),
			psoContainer.get()
		)
	);
	Logger::Log("Instantiate: PSO_Creator", fileName);
	Logger::Log("Instantiate: psoAssembler", fileName);


	diplomat.reset
	(
		new PSO_ContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, psoCreator.get())
		)
	);

	Logger::End("PSO_Context: Constructor");

}

PSO_Context::~PSO_Context()
{

}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////