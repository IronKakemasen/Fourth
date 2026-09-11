#include "PreCompileHeader.h"
#include "WindowContextToolLender.h"


WindowContext::ToolLender::ToolLender
(
	NexusFieldProof proof_,
	HWND const& HWND_
)
{
	std::get<HWND>(tools) = HWND_;
}
