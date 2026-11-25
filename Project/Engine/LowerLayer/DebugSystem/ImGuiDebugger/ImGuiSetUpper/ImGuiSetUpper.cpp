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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsClassic();
	ImGui_ImplWin32_Init(windowHandle);

	//deviceが必要なImGui初期化関数を呼んでもらう
	//auto& deviceAgent = deviceContextDip_.Access<DeviceContext::CommandExecutor>().
	//	CallImGuiInit
	//	(
	//		DeviceContext::CommandExecutor::DebugContextProof{},
	//		kImGuiRtvformat,
	//	)



	//srvFormat,srvDescriptor,handle

#endif
}
