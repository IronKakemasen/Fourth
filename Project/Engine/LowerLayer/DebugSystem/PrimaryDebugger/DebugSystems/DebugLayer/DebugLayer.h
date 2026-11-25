#pragma once
#include "../../PrimaryDebugger.h"


class DebugContext::PrimaryDebugger::DebugLayer
{
	Microsoft::WRL::ComPtr <ID3D12Debug1> debugController = nullptr;

public:

	DebugLayer(NexusFieldProof proof_);
	
};

