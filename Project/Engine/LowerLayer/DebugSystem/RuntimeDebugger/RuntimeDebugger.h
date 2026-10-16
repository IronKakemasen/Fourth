#pragma once
#include "../DebugContext.h"

class DebugContext::RuntimeDebugger
{
	class DebugLayer;
	class PointerValidator;
	class LeakChecker;

public:

	RuntimeDebugger(NexusFieldProof proof_);
	~RuntimeDebugger();

private:

	std::unique_ptr<DebugLayer> debugLayer;
	std::unique_ptr<PointerValidator> pointerValidator;
	std::unique_ptr<LeakChecker> leakChecker;
};


