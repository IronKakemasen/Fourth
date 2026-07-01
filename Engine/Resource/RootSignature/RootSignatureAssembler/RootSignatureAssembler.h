#pragma once
#include "../RootSignatureContext.h"


class RootSignatureContext::Assembler
{
public:
	Assembler(RootSignatureContext::InstanceKey key_, RootSignatureContext::CommandCreateRootSignature cmd_);
	~Assembler();

private:

	RootSignatureContext::CommandCreateRootSignature cmdCreaterootSignature;
};

