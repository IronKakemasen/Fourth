#pragma once
#include "../DeviceContext.h"


class DeviceContext::Setupper
{
public:

	Setupper(InstanceKey instanceKey_);

	//DeviceContextにコアパーツを渡す
	[[nodiscard]] std::tuple<Microsoft::WRL::ComPtr<IDXGIAdapter4>, Microsoft::WRL::ComPtr<ID3D12Device8>, Microsoft::WRL::ComPtr<IDXGIFactory7>>
		HandOver(DeviceContext::InstanceKey instanceKey_);

private:

	class EngineRequiementsChecker;

	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;

	void CreateDXGI_Factory();
	void FetchAdapter();
	void CreateDevice();
	void SetDebugLayerFilter();
};


