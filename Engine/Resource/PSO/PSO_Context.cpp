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


PSO_Context::PSO_Context(InstanceKey key_, ShaderContext& shaderContext_)
{
	Logger::Entry("PSO_Context: Constructor");
	
	InstantiatePSO_Assembler(key_, shaderContext_);

	Logger::End("PSO_Context: Constructor");

}

PSO_Context::~PSO_Context()
{

}
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
///+//////////////////////////////////////////////////////////////////////////////////////////////////////
void PSO_Context::InstantiatePSO_Assembler(InstanceKey key_, ShaderContext& shaderContext_)
{
	//PSO構築のためにshaderLibraryにアクセスさせてもらう
	auto* shaderLibrary = shaderContext_.AllowAccessToLibrary(ShaderContext::ShaderLibraryAccessKey{});

	assembler.reset(new Assembler(key_, shaderLibrary));
	Logger::Log("Instantiate: psoAssembler");
}