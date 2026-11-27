#include "PreCompileHeader.h"
#include "ImGuiDebugger.h"
#include "ImGuiSetUpper/ImGuiSetUpper.h"
#include "ImGuiInclude.h"

//外部
#include "../../Core/Command/CommandContextDiplomats.h"

#include "ImGuiInterface/ImGuiInterface.h"
#include "../../../Math/Vector/Vector3.h"
#include "../../../Math/Vector/Vector4.h"


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

	{
		static int       counter = 0;
		static bool      enabled = true;
		static int       level = 3;
		static float     gain = 0.5f;
		static Vector3   position = Vector3(0.0f, 0.0f, 0.0f);
		static Vector4<float> color(1.0f, 0.5f, 0.2f, 1.0f);

		ImGuiInterface::Window window("Sample Window",ImGuiInterface::WindowAttach::kNoMove);
		if (window)
		{
			ImGuiInterface::Text("Hello, ImGui!");
			ImGuiInterface::Separator();

			if (ImGuiInterface::Button("Click me")) ++counter;
			ImGuiInterface::Text("Clicked: %d times", counter);

			ImGuiInterface::Separator();

			ImGuiInterface::Text("enabled=%d level=%d gain=%.2f", enabled, level, gain);

			ImGuiInterface::RadioButton("radio", 3,3);

			ImGuiInterface::BeginChild("AAAAA");

			ImGuiInterface::Checkbox("Enabled", &enabled);
			ImGuiInterface::Slider("Level", level, 0, 10);          // int 版
			ImGuiInterface::Slider("Gain", gain, 0.0f, 1.0f);       // float 版
			ImGuiInterface::DragVector3("Position", position);      // 速度は省略(0.01f)
			ImGuiInterface::ColorEdit4("Color", color);

			ImGuiInterface::EndChild();

		}
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
