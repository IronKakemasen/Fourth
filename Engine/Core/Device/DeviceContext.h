#pragma once

class WinApp;


class DeviceContext
{
public:

	struct CreateKey;
	struct DevicePtrKey;

	DeviceContext(CreateKey createKey_);
	ID3D12Device8* GetDevicePtr(DevicePtrKey devicePtrKey_);

private:

	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;

	void CreateDevice();
};


//生成できるのはWinAppのみ
struct DeviceContext::CreateKey
{
private:
	friend class WinApp;
	explicit CreateKey() = default;
};


//Deviceのポインターを取得できるクラスの制限
struct DeviceContext::DevicePtrKey
{
private:
	friend class WinApp;
	explicit DevicePtrKey() = default;
};
