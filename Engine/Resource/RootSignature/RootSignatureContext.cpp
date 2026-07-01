#include "PreCompileHeader.h"
#include "RootSignatureContext.h"


//ツール
#include "RootSignatureAssembler/RootSignatureAssembler.h"

namespace
{
	auto const fileName = "RootSignatureContext.cpp";
}

RootSignatureContext::RootSignatureContext(InstanceKey key_, CommandCreateRootSignature cmdCreateRootSignature_)
{
	Logger::Entry("RootSignatureContext: Constructor");

	assembler.reset(new Assembler(key_, cmdCreateRootSignature_));
	Logger::Log("Instantiate: RootSignatureAssembler", fileName);


	Logger::End("RootSignatureContext: Constructor");
}

RootSignatureContext::~RootSignatureContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////