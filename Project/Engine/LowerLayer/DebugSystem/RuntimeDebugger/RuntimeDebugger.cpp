#include "RuntimeDebugger.h"
#include "DebugSystems/DebugLayer/DebugLayer.h"
#include "DebugSystems/PointerValidator/PointerValidator.h"
#include "DebugSystems/LeakChecker/LeakChecker.h"

DebugContext::RuntimeDebugger::RuntimeDebugger(NexusFieldProof proof_)
{
	using namespace ProjectConfig::Debug;

	//インスタンス制限
	std::string errorMessage = "RuntimeDebuggerクラスが複数具現化されてます";
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), errorMessage,"RuntimeDebugger.cpp");

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
//RuntimeDebuggerクラスのインスタンスを1つに制限する
bool DebugContext::RuntimeDebugger::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

