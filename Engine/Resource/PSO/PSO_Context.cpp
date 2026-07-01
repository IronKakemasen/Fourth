#include "PreCompileHeader.h"
#include "PSO_Context.h"

//ツール
#include"PSO_Assembler/PSO_Assembler.h"

//外部
#include "../Shader/ShaderContext.h"

class ShaderLibrary;

namespace
{
	auto const fileName = "PSO_Context.cpp";
}


PSO_Context::PSO_Context
(
	InstanceKey key_,
	ShaderContext& shaderContext_,
	CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
	CommandCreateComputePSO cmdCreateComputePSO_
)
{
	Logger::Entry("PSO_Context: Constructor");
	
	//PSO構築のためにshaderLibraryにアクセスさせてもらう
	//auto* shaderLibrary = shaderContext_.AllowAccessToLibrary(ShaderContext::ShaderLibraryAccessKey{});

	InstantiatePSO_Assembler(key_, cmdCreateGraphicsPSO_, cmdCreateComputePSO_);

	Logger::End("PSO_Context: Constructor");

}

PSO_Context::~PSO_Context()
{

}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
void PSO_Context::InstantiatePSO_Assembler
(
	InstanceKey key_,
	CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
	CommandCreateComputePSO cmdCreateComputePSO_
)
{
	assembler.reset(new Assembler(key_, cmdCreateGraphicsPSO_, cmdCreateComputePSO_));
	Logger::Log("Instantiate: psoAssembler");
}