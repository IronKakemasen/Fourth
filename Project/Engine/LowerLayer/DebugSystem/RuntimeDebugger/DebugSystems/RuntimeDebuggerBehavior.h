#pragma once

class RuntimeDebugger;

class RuntimeDebuggerBehavior
{
public:
	struct InstanceKey
	{
	private:
		friend class RuntimeDebugger;
		explicit InstanceKey() = default;
	};

protected:

	virtual void Init() = 0;
	RuntimeDebuggerBehavior(InstanceKey instanceKey_) {};
};

