#include "PSO_Context.h"

//ツール
#include"PSO_Assembler/PSO_Assembler.h"


namespace
{
	auto const fileName = "PSO_Context.cpp";
}


PSO_Context::PSO_Context
(
	InstanceKey key_,
	DeviceContextDiplomat* deviceContextDiplomat_
)
{
	Logger::Entry("PSO_Context: Constructor");
	
	assembler.reset(new Assembler(key_, deviceContextDiplomat_, &psoContainer));
	Logger::Log("Instantiate: psoAssembler");


	Logger::End("PSO_Context: Constructor");

}

PSO_Context::~PSO_Context()
{

}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////