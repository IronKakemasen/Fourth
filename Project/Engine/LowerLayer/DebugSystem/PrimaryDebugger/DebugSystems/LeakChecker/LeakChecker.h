#pragma once
#include "../../PrimaryDebugger.h"

class DebugContext::PrimaryDebugger::LeakChecker
{
public:

	LeakChecker(NexusFieldProof proof_);
	~LeakChecker();

	LeakChecker(const LeakChecker&) = delete;
	LeakChecker& operator=(const LeakChecker&) = delete;
};

