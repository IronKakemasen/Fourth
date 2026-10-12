#pragma once
#include "RootSignatureCmdProvider.h"

class RenderContext;

struct RootSignatureContext::CmdProvider::UsesCreateGraphicsRootSigCmdLicence
{
private:

	friend class RenderContext;
	explicit UsesCreateGraphicsRootSigCmdLicence() = default;

};
