#include "PreCompileHeader.h"
#include "DebugContext.h"
#include "RuntimeDebugger/RuntimeDebugger.h"


DebugContext::DebugContext(NexusFieldProof proof_)
{
	Logger::Entry("DebugContext: Constructor");

#ifdef _DEBUG

	runtimeDebugger = std::make_unique<RuntimeDebugger>(proof_);
	Logger::Log("Instantiate: RuntimeDebugger", "DebugContext.cpp");

#endif // DEBUG


	Logger::End("DebugContext: Constructor");
}


DebugContext::~DebugContext()
{

}
