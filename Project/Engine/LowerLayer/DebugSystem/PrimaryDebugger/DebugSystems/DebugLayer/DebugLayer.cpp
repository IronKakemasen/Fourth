
#include "DebugLayer.h"


DebugContext::PrimaryDebugger::DebugLayer::DebugLayer(NexusFieldProof proof_)
{
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
}

