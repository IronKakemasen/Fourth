#pragma once
#include "DebugSystems/DebugLayer/DebugLayer.h"
#include "DebugSystems/LeakChecker/LeakChecker.h"
#include "DebugSystems/PointerValidator/PointerValidator.h"

class RuntimeDebugger
{
public:

	RuntimeDebugger();

	RuntimeDebugger(const RuntimeDebugger&) = delete;
	RuntimeDebugger& operator=(const RuntimeDebugger&) = delete;
	RuntimeDebugger(RuntimeDebugger&&) = delete;
	RuntimeDebugger& operator=(RuntimeDebugger&&) = delete;

private:

	//インスタンス制限
	class InstanceLimiter;

	DebugLayer debugLayer{ RuntimeDebuggerBehavior::InstanceKey{} };
	PointerValidator pointerValidator{ RuntimeDebuggerBehavior::InstanceKey{} };
	LeakChecker leakChecker{ RuntimeDebuggerBehavior::InstanceKey{} };
};


//RuntimeDebuggerクラスのインスタンスを制御するクラス
class RuntimeDebugger::InstanceLimiter
{
public:
	static bool CanInstantiate();

	InstanceLimiter(const InstanceLimiter&) = delete;
	InstanceLimiter& operator=(const InstanceLimiter&) = delete;
	InstanceLimiter(InstanceLimiter&&) = delete;
	InstanceLimiter& operator=(InstanceLimiter&&) = delete;

private:
	int instanceCnt{};

	~InstanceLimiter() = default;
	InstanceLimiter() = default;
};


