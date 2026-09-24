#pragma once
#include "../RuntimeDebuggerBehavior.h"

class PointerValidator :public RuntimeDebuggerBehavior
{
public:
	virtual void Init()override;
	PointerValidator(InstanceKey instanceKey_) :RuntimeDebuggerBehavior(instanceKey_) {}

};

