#include "RuntimeDebugger.h"
#include "DebugSystems/DebugLayer/DebugLayer.h"
#include "DebugSystems/PointerValidator/PointerValidator.h"
#include "DebugSystems/LeakChecker/LeakChecker.h"

DebugContext::RuntimeDebugger::RuntimeDebugger(NexusFieldProof proof_)
{
	using namespace ProjectConfig::Debug;

	if (kEnableDebugLayer) debugLayer = std::make_unique<DebugLayer>(proof_);
	if (kEnablePointerValidator) pointerValidator = std::make_unique<PointerValidator>(proof_);
	if (kEnableLeakChecker) leakChecker = std::make_unique<LeakChecker>(proof_);

}

DebugContext::RuntimeDebugger::~RuntimeDebugger()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
