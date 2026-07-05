
#include "RootSignatureContext.h"
#include "RootSignatureLibrary/RootSignatureLibrary.h"

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

	rootSignatureLibrary.reset(new RootSignatureLibrary(RootSignatureLibrary::InstanceKey{}, assembler.get()));
	Logger::Log("Instantiate: rootSignatureLibrary", fileName);


	Logger::End("RootSignatureContext: Constructor");
}

RootSignatureContext::~RootSignatureContext()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////