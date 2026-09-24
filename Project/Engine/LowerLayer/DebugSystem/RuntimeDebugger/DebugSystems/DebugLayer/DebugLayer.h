#pragma once
#include "../RuntimeDebuggerBehavior.h"

class DebugLayer:public RuntimeDebuggerBehavior
{
	Microsoft::WRL::ComPtr <ID3D12Debug1> debugController = nullptr;

public:
	virtual void Init()override;
	DebugLayer(InstanceKey instanceKey_) :RuntimeDebuggerBehavior(instanceKey_) {}
	
};

