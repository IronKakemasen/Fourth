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

	RuntimeDebugger(const RuntimeDebugger&) = delete;
	RuntimeDebugger& operator=(const RuntimeDebugger&) = delete;
	RuntimeDebugger(RuntimeDebugger&&) = delete;
	RuntimeDebugger& operator=(RuntimeDebugger&&) = delete;

private:

	//なんかの間違いで複数インスタンス化されると特に困るんでインスタンス制限
	class InstanceLimiter;

	std::unique_ptr<DebugLayer> debugLayer;
	std::unique_ptr<PointerValidator> pointerValidator;
	std::unique_ptr<LeakChecker> leakChecker;
};


//RuntimeDebuggerクラスのインスタンスを制御するクラス
class DebugContext::RuntimeDebugger::InstanceLimiter
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


