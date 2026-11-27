#pragma once
#include "../DebugContext.h"


class DebugContext::ImGuiDebugger
{
	class SetUpper;
		
public:

	ImGuiDebugger
	(
		NexusFieldProof proof_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

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

	static float constexpr kSceneViewScaleX = 0.625f;
	static float constexpr kSceneViewScaleY = 0.43f;


};

