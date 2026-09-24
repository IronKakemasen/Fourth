
#include "RuntimeDebugger.h"
#include "../ErrorMessageOutput/ErrorMessageOutput.h"


RuntimeDebugger::RuntimeDebugger()
{
	using namespace ProjectConfig::Debug;

	//インスタンス制限
	std::string errorMessage = "RuntimeDebuggerクラスが複数具現化されてます";
	ErrorMessageOutput::Assert::DetectError(InstanceLimiter::CanInstantiate(), errorMessage,"RuntimeDebugger.cpp");

	if (kEnableDebugLayer) debugLayer.Init();
	if (kEnablePointerValidator) pointerValidator.Init();
	if (kEnableLeakChecker) leakChecker.Init();

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RuntimeDebuggerクラスのインスタンスを1つに制限する
bool RuntimeDebugger::InstanceLimiter::CanInstantiate()
{
	static InstanceLimiter instanceLimiter;

	return (instanceLimiter.instanceCnt++ == 0);
}

