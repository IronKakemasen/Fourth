#pragma once
#include "../DeviceContext.h"


class DeviceContext::Setupper
{
public:
	Setupper(InstanceKey instanceKey_);

	[[nodiscard]] Microsoft::WRL::ComPtr<IDXGIAdapter4> HandOverAdapter(DeviceContext::InstanceKey instanceKey_);
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Device8> HandOverDevice(DeviceContext::InstanceKey instanceKey_);
	[[nodiscard]] Microsoft::WRL::ComPtr<IDXGIFactory7> HandOverDxgiFactory(DeviceContext::InstanceKey instanceKey_);

private:

	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;

	void CreateDXGI_Factory();
	void FetchAdapter();
	void CreateDevice();
	void ShaderModelChack(D3D_SHADER_MODEL shaderModel_);
	void IsMeshShaderSupported();
	void SetDebugLayerFilter();
};


