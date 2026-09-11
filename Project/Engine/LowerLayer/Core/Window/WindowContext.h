#pragma once

class Nexus;

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

	struct NexusFieldProof;

	WindowContext(NexusFieldProof proof_);
	void Finalize();
	HWND WatchHWND();

private:

	static LRESULT CALLBACK WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);
};


struct WindowContext::NexusFieldProof
{
private:
	friend class Nexus;
	explicit NexusFieldProof() = default;
};
