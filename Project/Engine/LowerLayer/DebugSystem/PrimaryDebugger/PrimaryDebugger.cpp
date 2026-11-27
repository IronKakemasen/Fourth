#include "PrimaryDebugger.h"
#include "DebugSystems/DebugLayer/DebugLayer.h"
#include "DebugSystems/PointerValidator/PointerValidator.h"
#include "DebugSystems/LeakChecker/LeakChecker.h"

DebugContext::PrimaryDebugger::PrimaryDebugger(NexusFieldProof proof_)
{
	using namespace ProjectConfig::Debug;

#ifdef _DEBUG

	if (kEnableDebugLayer) debugLayer = std::make_unique<DebugLayer>(proof_);
	if (kEnablePointerValidator) pointerValidator = std::make_unique<PointerValidator>(proof_);
	if (kEnableLeakChecker) leakChecker = std::make_unique<LeakChecker>(proof_);

#endif // _DEBUG

}

DebugContext::PrimaryDebugger::~PrimaryDebugger()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
