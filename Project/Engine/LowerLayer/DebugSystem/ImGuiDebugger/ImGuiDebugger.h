#pragma once
#include "../DebugContext.h"


class DebugContext::ImGuiDebugger
{
	class SetUpper;
	class HierarchyWindow;

public:

	ImGuiDebugger
	(
		NexusFieldProof proof_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

	~ImGuiDebugger();

	void BeginNewFrame
	(
		NexusFieldProof proof_,
		AgentKey key_
	);

	void Render
	(
		AgentKey key_,
		D3D12_GPU_DESCRIPTOR_HANDLE finalRefBufferGpuHandle_,
		CommandContextDiplomat& commandContextDiplomat_
	);

private:

	std::unique_ptr<HierarchyWindow> hierarchyWindow;


};

