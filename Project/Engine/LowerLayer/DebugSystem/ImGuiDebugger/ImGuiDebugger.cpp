#include "PreCompileHeader.h"
#include "ImGuiDebugger.h"
#include "ImGuiSetUpper/ImGuiSetUpper.h"
#include "ImGuiInclude.h"
#include "ImGuiInterface/ImGuiInterface.h"
#include "HierarchyWindow/HierarchyWindow.h"

//外部
#include "../../Core/Command/CommandContextDiplomats.h"


using namespace ProjectConfig;
using namespace ProjectConfig::Debug;

namespace
{
	auto const fileName = "ImGuiDebugger.cpp";
}

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

	hierarchyWindow = std::make_unique<HierarchyWindow>();
	Logger::Log("Instantiate: hierarchyWindow", fileName);
}

DebugContext::ImGuiDebugger::~ImGuiDebugger() {}

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

	static float const imageWidth  = ImGuiLayout::kSceneViewImageRateX * (float)Window::Width();
	static float const imageheight = ImGuiLayout::kSceneViewImageRateY * (float)Window::Height();

	//ウィンドウの位置とサイズを決定
	ImGuiInterface::SetNextWindowSize(ImGuiLayout::kSceneViewWindowRateX, ImGuiLayout::kSceneViewWindowRateY);
	ImGuiInterface::SetNextWindowPos(ImGuiLayout::kHierarchyWindowRateX, 0.0f);

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
