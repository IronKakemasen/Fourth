#pragma once

class DeviceContext
{
	struct Parts
	{
		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	};

	Parts parts;

public:
	DeviceContext();


private:
	void CreateDevice();
};

