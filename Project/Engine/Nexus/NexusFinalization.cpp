#include "Nexus.h"
#include "../LowerLayer/Core/Command/CommandContext.h"
#include "../LowerLayer/Core/Window/WindowContext.h"

namespace
{
	std::string const fileName = "Nexus.cpp";
}


void Nexus::Finalize()
{
	commandContext->Finalize(CommandContext::InstanceKey{});
	windowContext->Finalize();
}
