#include "Nexus.h"
#include "../LowerLayer/Core/Command/CommandContext.h"
#include "../LowerLayer/Core/Window/WindowContextDiplomat/WindowContextExecutionAgent/WindowContextExecutionAgent.h"
#include "../LowerLayer/Core/Window/WindowContextDiplomat/WindowContextDiplomat.h"
#include "../LowerLayer/DebugSystem/ImGuiDebugger/ImGuiInclude.h"

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
	auto& agent = windowContext->AccessDiplomat().Access<WindowContext::ExecutionAgent>();
	agent.WindowContextFinalize(WindowContext::NexusFieldProof{});
}

template<>
void Nexus::Finalize<Nexus::FinalizeSequence::kImGuiFinalization>()
{

#ifndef NDEBUG

	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

#endif

}



template
void Nexus::Finalize<Nexus::FinalizeSequence::kWindowContext>();
template
void Nexus::Finalize<Nexus::FinalizeSequence::kCommandContext>();
template
void Nexus::Finalize<Nexus::FinalizeSequence::kImGuiFinalization>();
