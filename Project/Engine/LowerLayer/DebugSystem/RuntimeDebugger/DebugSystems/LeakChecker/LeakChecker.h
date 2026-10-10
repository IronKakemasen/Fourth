#pragma once
#include "../../RuntimeDebugger.h"

class DebugContext::RuntimeDebugger::LeakChecker
{
public:

	LeakChecker(NexusFieldProof proof_);
	~LeakChecker();

	LeakChecker(const LeakChecker&) = delete;
	LeakChecker& operator=(const LeakChecker&) = delete;
};

