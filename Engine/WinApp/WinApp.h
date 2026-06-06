#pragma once
#include "../Core/Window/WindowContext.h"
#include "../Resource/GPUBufferCreator/GPUBufferCreator.h"
#include "../Core/Device/DeviceContext.h"


class WinApp
{
public:

	~WinApp();
	WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_);

	WinApp(const WinApp&) = delete;
	WinApp& operator=(const WinApp&) = delete;
	WinApp(WinApp&&) = delete;
	WinApp& operator=(WinApp&&) = delete;

private:

	//WinAppのインスタンスを1つに制限するためのシングルトンクラス
	class InstanceLimiter;

	//IDXGIFactory7、IDXGIAdapter4、ID3D12Device8を持っている。
	std::unique_ptr<DeviceContext> deviceContext;
	//GPUリソースを作るもの
	std::unique_ptr<GPUBufferCreator> gpuBufferCreator;
	//ウィンドウを制御するもの
	std::unique_ptr<WindowContext> windowContext;

	//メンバー変数のインスタンス化
	void InstantiateMemberVariables(uint32_t width_, uint32_t height_, LPCWSTR windowName_);
	//コマンドの受け渡し（GPUresourceCreateなど）
	void GivingAndReceivingCommands();

};


//WinAppクラスのインスタンスを制御するクラス
class WinApp::InstanceLimiter
{
public:
	static bool CanInstantiate();

	InstanceLimiter(const InstanceLimiter&) = delete;
	InstanceLimiter& operator=(const InstanceLimiter&) = delete;
	InstanceLimiter(InstanceLimiter&&) = delete;
	InstanceLimiter& operator=(InstanceLimiter&&) = delete;

private:
	int instanceCnt{};

	~InstanceLimiter() = default;
	InstanceLimiter() = default;
};

