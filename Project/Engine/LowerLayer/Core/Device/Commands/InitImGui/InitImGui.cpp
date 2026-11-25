#include "PreCompileHeader.h"
#include "InitImGui.h"
#include "../../../../DebugSystem/ImGuiDebugger/ImGuiInclude.h"


InitImGui::InitImGui(DeviceContext::GenerateKey generateKey_)
	:DeviceContextCommandBehavior(generateKey_)
{

}

void InitImGui::ImplDX12Init
(
	ID3D12Device8* device_,
	DXGI_FORMAT format_,
	ID3D12DescriptorHeap* srvUavDescriptorHeap_,
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_,
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_
)
{
#ifndef NDEBUG

	ImGui_ImplDX12_Init
	(
		device_,
		(UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer,
		format_,
		srvUavDescriptorHeap_,
		cpuHandle_,
		gpuHandle_
	);

#endif // !NDEBUG


}
