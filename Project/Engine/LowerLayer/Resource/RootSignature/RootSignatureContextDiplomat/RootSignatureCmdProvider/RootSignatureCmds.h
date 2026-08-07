#pragma once
#include "../../RootSignatureCreator/RootSignatureAssembler/RootSignatureDesc.h"

namespace RootSignatureCmds 
{
	using CreateGraphicsRootSigCmd = std::function<ID3D12RootSignature* (const RootSignatureDesc::Graphics&)>;
}