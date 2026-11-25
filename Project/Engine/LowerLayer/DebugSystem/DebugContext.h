#pragma once

class Nexus;
class WindowContextDiplomat;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;
class DebugContextDiplomat;

class DebugContext
{
public:

	class ImGuiDebugger;
	class ExecutionAgent;

	//ネクサスフィールドの証
	struct NexusFieldProof;
	struct AgentKey;

	DebugContext
	(
		NexusFieldProof proof_
	);

	~DebugContext();

	void InstantiateImguiDebugger
	(
		NexusFieldProof proof_,
		AgentKey key_,
		WindowContextDiplomat& windowContextDip_,
		DeviceContextDiplomat& deviceContextDip_,
		DescriptorHeapContextDiplomat& descriptorHeapContextDip_
	);

	auto& AccessDiplomat() { return *diplomat; }

private:

	class PrimaryDebugger;

	std::unique_ptr<ImGuiDebugger> imGuiDebugger;
	std::unique_ptr<PrimaryDebugger> primaryDebugger;
	std::unique_ptr<DebugContextDiplomat> diplomat;
};


struct DebugContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};


struct DebugContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};

