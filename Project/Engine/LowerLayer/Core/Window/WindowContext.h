#pragma once

class Nexus;
class WindowContextDiplomat;

class WindowContext
{
	class Builder;
	class WindowProcedure;
	struct AgentKey;

	struct CoreParts
	{
		HINSTANCE hInst;
		HWND hWnd;
		UINT width;
		UINT height;
		LPCWSTR windowName;
	}coreParts;

public:
	class ToolLender;
	class ExecutionAgent;

	struct NexusFieldProof;

	WindowContext(NexusFieldProof proof_);
	~WindowContext();

	void Finalize(NexusFieldProof proof_, AgentKey agentKey_);

	std::unique_ptr<WindowContextDiplomat> diplomat;

};


struct WindowContext::NexusFieldProof
{
private:
	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct WindowContext::AgentKey
{
private:
	friend class ExecutionAgent;
	explicit AgentKey() = default;
};


