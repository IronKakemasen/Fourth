#include "PreCompileHeader.h"
#include "ImGuiDebugger.h"
#include "ImGuiSetUpper/ImGuiSetUpper.h"
#include "ImGuiInclude.h"

//外部
#include "../../Core/Command/CommandContextDiplomats.h"


using namespace ProjectConfig;


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

}

void DebugContext::ImGuiDebugger::Render
(
	AgentKey key_,
	D3D12_GPU_DESCRIPTOR_HANDLE finalRefBufferGpuHandle_,
	CommandContextDiplomat& commandContextDiplomat_
) 
{
#ifndef NDEBUG

	static float const imageWidth  = Debug::ImGuiLayout::kSceneViewImageRateX * (float)Window::Width();
	static float const imageheight = Debug::ImGuiLayout::kSceneViewImageRateY * (float)Window::Height();


	static float const windowWidth  = Debug::ImGuiLayout::kSceneViewWindowRateX * (float)Window::Width();
	static float const windowHeight = Debug::ImGuiLayout::kSceneViewWindowRateY * (float)Window::Height();

	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);

	//最終描画結果をImGUiウィンドウで描画
	ImGui::Begin
	(
		"SceneView",
		nullptr, 
		ImGuiWindowFlags_NoMove		|
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize
	);


	ImGui::Image
	(
		ImMapTextures(finalRefBufferGpuHandle_.ptr), 
		ImVec2(imageWidth, imageheight)
	);
	ImGui::End();

	//コマンドリストを借りる
	auto* cndList = &commandContextDiplomat_.Access<CommandContext::ToolLender>().
		Lend<ID3D12GraphicsCommandList6>(CommandContext::ToolLender::LicenceType<ID3D12GraphicsCommandList6>{});

	ImGui::Render();
	//commandListにImguiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cndList);

#endif

}
