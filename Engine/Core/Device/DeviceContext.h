#pragma once

class WinApp;


class DeviceContext
{
public:

	//生成キー。WinAppしか許さない
	struct CreateKey;
	//GPUバッファを生成を許可するキー。デバイスは渡さず、コマンドを渡す
	struct BufferCreationPermitKey;

	DeviceContext(CreateKey createKey_);

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


//生成できるのはWinAppのみ
struct DeviceContext::CreateKey
{
private:

	friend class WinApp;

	explicit CreateKey() = default;
};


//バッファ生成関数群を取得できるクラスの制限
struct DeviceContext::BufferCreationPermitKey
{
private:
	friend class WinApp;
	explicit BufferCreationPermitKey() = default;
};
