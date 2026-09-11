#pragma once

class Nexus;
class WindowContextDiplomat;

class WindowContext
{
	class Builder;

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
	struct AgentKey;

	WindowContext(NexusFieldProof proof_);
	~WindowContext();

	void Finalize(NexusFieldProof proof_, AgentKey agentKey_);

	std::unique_ptr<WindowContextDiplomat> diplomat;

private:

	static LRESULT CALLBACK WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);
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


