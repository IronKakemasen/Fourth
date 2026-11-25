#include "PreCompileHeader.h"
#include "ImGuiDebugger.h"
#include "ImGuiSetUpper/ImGuiSetUpper.h"
#include "ImGuiInclude.h"

//外部
#include "../../Core/Command/CommandContextDiplomats.h"



DebugContext::ImGuiDebugger::ImGuiDebugger
(
	NexusFieldProof proof_,
	WindowContextDiplomat& windowContextDip_,
	DeviceContextDiplomat& deviceContextDip_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDip_
) 
{
	SetUpper::InitializeImGui
	(
		proof_,
		windowContextDip_,
		deviceContextDip_,
		descriptorHeapContextDip_
	);
}

void DebugContext::ImGuiDebugger::BeginNewFrame
(
	NexusFieldProof proof_,
	AgentKey key_
)
{

#ifndef NDEBUG

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#endif

#ifndef NDEBUG
	static bool showWindow = true;
	static int counter = 0;

	if (showWindow)
	{
		ImGui::Begin("Nexus Debug Window", &showWindow);

		ImGui::Text("Hello, ImGui!");
		ImGui::Text("This is a test window.");

		if (ImGui::Button("Click me"))
		{
			++counter;
		}

		ImGui::Text("Button clicked: %d times", counter);

		ImGui::End();
	}
#endif

}

void DebugContext::ImGuiDebugger::Render
(
	AgentKey key_,
	CommandContextDiplomat& commandContextDiplomat_
) 
{
#ifndef NDEBUG

	//コマンドリストを借りる
	auto* cndList = &commandContextDiplomat_.Access<CommandContext::ToolLender>().
		Lend<ID3D12GraphicsCommandList6>(CommandContext::ToolLender::LicenceType<ID3D12GraphicsCommandList6>{});

	ImGui::Render();
	//commandListにImguiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cndList);

#endif

}
