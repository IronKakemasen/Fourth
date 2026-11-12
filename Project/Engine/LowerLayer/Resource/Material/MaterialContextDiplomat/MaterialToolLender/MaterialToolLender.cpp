#include "PreCompileHeader.h"
#include "MaterialToolLender.h"


MaterialContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	MaterialAttacher* materialAttacher_
)
{
	std::get<MaterialAttacher*>(tools) = materialAttacher_;
}
