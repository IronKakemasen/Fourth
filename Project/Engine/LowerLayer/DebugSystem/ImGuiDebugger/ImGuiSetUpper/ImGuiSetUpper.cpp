#include "PreCompileHeader.h"
#include "ImGuiSetUpper.h"
#include "../ImGuiInclude.h"


//外部
#include "../../../Core/Window/WindowContextDiplomat/WindowContextDiplomat.h"
#include "../../../Core/Window/WindowContextDiplomat/WindowContextToolLender/WindowContextToolLender.h"
#include "../../../Core/Window/WindowContextDiplomat/WindowContextToolLender/WindowContextToolLenderLicences.h"

#include "../../../Core/Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../../Core/Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"
#include "../../../Core/Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceCmdExecutorLicences.h"

#include "../../../Core/DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapContextDiplomat.h"
#include "../../../Core/DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLender.h"
#include "../../../Core/DescriptorHeap/DescriptorHeapContextDiplomat/DescriptorHeapToolLender/DescriptorHeapToolLenderLicences.h"
#include "../../../Core/DescriptorHeap/ViewCreator/ViewCreator.h"




void DebugContext::ImGuiDebugger::SetUpper::InitializeImGui
(
	NexusFieldProof proof_,
	WindowContextDiplomat& windowContextDip_,
	DeviceContextDiplomat& deviceContextDip_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDip_
)
{
#ifndef NDEBUG

	//ウィンドウのハンドルを借りる
	auto& windowHandle = windowContextDip_.Access<WindowContext::ToolLender>().
		Lend<HWND>(WindowContext::ToolLender::LicenceType<HWND>{});

	//srvUavのディスクリプタヒープとビュークリエイターを借りる
	auto& descriptorHeapToolLender = 
		descriptorHeapContextDip_.Access<DescriptorHeapContext::ToolLender>();
	auto* srvDescriptorHeap = 
		&descriptorHeapToolLender.Lend<ID3D12DescriptorHeap>(DescriptorHeapContext::ToolLender::LicenceType<ID3D12DescriptorHeap>{});
	auto& viewCreator = 
		descriptorHeapToolLender.Lend<DescriptorHeapContext::ViewCreator>(DescriptorHeapContext::ToolLender::LicenceType<DescriptorHeapContext::ViewCreator>{});

	//予約しておいたImGui用のdescriptorHeapのハンドル
	auto const& imguiHandle = viewCreator.WatchReservedHeapHandles
		<DescriptorHeapContext::ViewCreator::HeapType::kSRVUAV>((UINT)DescriptorHeapContext::ViewCreator::ReservedSrvIndex::kImGui);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	ImGui::StyleColorsClassic();

	ImGui_ImplWin32_Init(windowHandle);

	//deviceが必要なImGui初期化関数を呼んでもらう
	deviceContextDip_.Access<DeviceContext::CommandExecutor>().
	CallImGuiInit
	(
		DeviceContext::CommandExecutor::DebugContextProof{},
		ProjectConfig::Render::kSwapChainBufferFormat,
		srvDescriptorHeap,
		imguiHandle.cpu,
		imguiHandle.gpu
	);

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.5f, 0.5f, 0.1f, 1.0f));

	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));


	Logger::Log("Complete ImGui Initializing", "ImGuiSetUpper.cpp");

#endif
}
