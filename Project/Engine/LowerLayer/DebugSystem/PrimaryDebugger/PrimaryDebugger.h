#pragma once
#include "../DebugContext.h"

class DebugContext::PrimaryDebugger
{
	class DebugLayer;
	class PointerValidator;
	class LeakChecker;

public:

	PrimaryDebugger(NexusFieldProof proof_);
	~PrimaryDebugger();

private:

	std::unique_ptr<DebugLayer> debugLayer;
	std::unique_ptr<PointerValidator> pointerValidator;
	std::unique_ptr<LeakChecker> leakChecker;
};


