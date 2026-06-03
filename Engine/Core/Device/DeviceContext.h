#pragma once

class WinApp;
class GPUBufferCreator;


class DeviceContext
{
public:

	//生成キー。WinAppしか許さない
	struct InstanceKey;
	//デバイスにアクセスするのを許可するキー
	struct DeviceAccessKey;

	DeviceContext(InstanceKey instanceKey);
	~DeviceContext();

	//DeviceContextの中にコマンドをセット
	void SetGPU_CreationCommands(GPUBufferCreator* gpuBufferCreator_);

private:	
	//コマンド生成クラス
	class CommandGenerator;
	//Setupper
	class Setupper;
	//CommandExecutor
	class CommandExecutor;

	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;

	std::unique_ptr<CommandExecutor> commandExecutor;
	std::unique_ptr<CommandGenerator> commandGenerator;


	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandExecutorの生成
	void CreateCommandExecutor();
};


//生成できるのはWinAppのみ
struct DeviceContext::InstanceKey
{
private:

	friend class WinApp;
	explicit InstanceKey() = default;
};


//アクセスさせるがポインタは渡さん
struct DeviceContext::DeviceAccessKey
{
private:

	friend class CommandExecutor;
	explicit DeviceAccessKey() = default;
};



