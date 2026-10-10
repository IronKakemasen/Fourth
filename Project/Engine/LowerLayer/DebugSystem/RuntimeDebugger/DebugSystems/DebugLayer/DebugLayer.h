#pragma once
#include "../../RuntimeDebugger.h"


class DebugContext::RuntimeDebugger::DebugLayer
{
	Microsoft::WRL::ComPtr <ID3D12Debug1> debugController = nullptr;

public:

	DebugLayer(NexusFieldProof proof_);
	
};

