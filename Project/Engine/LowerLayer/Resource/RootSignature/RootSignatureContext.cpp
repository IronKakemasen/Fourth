#include "RootSignatureContext.h"
#include "RootSignatureLibrary/RootSignatureLibrary.h"

//ツール
#include "RootSignatureAssembler/RootSignatureAssembler.h"

namespace
{
	auto const fileName = "RootSignatureContext.cpp";
}

RootSignatureContext::RootSignatureContext(InstanceKey key_, DeviceContextDiplomat* deviceContextDiplomat_)
{
	Logger::Entry("RootSignatureContext: Constructor");

	assembler.reset(new Assembler(key_, deviceContextDiplomat_));
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