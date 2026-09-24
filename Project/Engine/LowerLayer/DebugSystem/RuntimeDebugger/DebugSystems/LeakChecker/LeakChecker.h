#pragma once
#include "../RuntimeDebuggerBehavior.h"

class LeakChecker :public RuntimeDebuggerBehavior
{
public:

	~LeakChecker();
	LeakChecker(InstanceKey instanceKey_) :RuntimeDebuggerBehavior(instanceKey_) {}


	virtual void Init()override;

	LeakChecker(const LeakChecker&) = delete;
	LeakChecker& operator=(const LeakChecker&) = delete;
};

