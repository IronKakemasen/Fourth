#pragma once
#include "../Core/Window/WindowContext.h"
#include "../Resource/GPUBufferCreator/GPUBufferCreator.h"
#include "../Core/Device/DeviceContext.h"
#include "../Core/DescriptorHeap/DescriptorHeapContext.h"


class WinApp
{
public:

	~WinApp();
	WinApp();

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
	//DescriptorHeapを作り、viewを生成するクラスを所持
	std::unique_ptr<DescriptorHeapContext> descriptorHeapContext;

	void InitDeviceContext();
	void InitGPUBufferCreator();
	void InitWindowContext();
	void InitDescriptorHeapContext();

};



