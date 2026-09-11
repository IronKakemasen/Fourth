#include "Nexus.h"
#include "../LowerLayer/Core/Command/CommandContext.h"
#include "../LowerLayer/Core/Window/WindowContextDiplomat/WindowContextExecutionAgent/WindowContextExecutionAgent.h"
#include "../LowerLayer/Core/Window/WindowContextDiplomat/WindowContextDiplomat.h"

namespace
{
	std::string const fileName = "NexusFinalization.cpp";
}


template<>
void Nexus::Finalize<Nexus::FinalizeSequence::kCommandContext>()
{
	commandContext->Finalize(CommandContext::NexusFieldProof{});
}

template<>
void Nexus::Finalize<Nexus::FinalizeSequence::kWindowContext>()
{
	//ウィンドウコンテキストの終了処理を代行してもらう
	auto& agent = windowContext->diplomat->Access<WindowContext::ExecutionAgent>();
	agent.WindowContextFinalize(WindowContext::NexusFieldProof{});
}

template<>
void Nexus::Finalize<Nexus::FinalizeSequence::kCoUninitialize>()
{
	//COMの終了
	CoUninitialize();
	Logger::Log("CoUninitialize", fileName);
}

