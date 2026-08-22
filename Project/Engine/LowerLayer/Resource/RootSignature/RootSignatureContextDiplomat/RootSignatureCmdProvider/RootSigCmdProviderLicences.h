#pragma once
#include "RootSignatureCmdProvider.h"
#include "../../../../Render/RenderContext.h"


struct RootSignatureContext::CmdProvider::UsesCreateGraphicsRootSigCmdLicence
{
private:

	friend class RenderContext::RenderGraph;
	explicit UsesCreateGraphicsRootSigCmdLicence() = default;

};
