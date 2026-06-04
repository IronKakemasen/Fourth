#pragma once

class WinApp;
class GPUBufferCreator;
class DeviceContextCommandBehavior;

struct ConstantBufferDescription;
struct ColorBufferDescription;


class DeviceContext
{
public:

	enum CommandType
	{
		//GPUリソース生成
		kCreatingGPU_Buffer,


		kCount
	};


	//コマンド生成クラス
	class CommandGenerator;
	//生成キー。WinAppしか許さない
	struct InstanceKey;
	//デバイスにアクセスするのを許可するキー
	struct DeviceAccessKey;

	DeviceContext(InstanceKey instanceKey);
	~DeviceContext();

	std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)>GetGetCreateConstantBufferCommand();
	std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)>GetGetCreateColorBufferCommand();

private:

	using CommandList = std::vector<std::unique_ptr<DeviceContextCommandBehavior>>;
	using CommandMap = std::unordered_map<CommandType, CommandList>;

	//Setupper
	class Setupper;
	//CommandExecutor
	class CommandExecutor;

	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;

	std::unique_ptr<CommandExecutor> commandExecutor;
	std::unique_ptr<CommandGenerator> commandGenerator;

	//コマンドのコンテナ
	CommandMap commandContainer;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandExecutorの生成
	void CreateCommandExecutor(DeviceContext::InstanceKey instanceKey_);
	//CommandGeneratorの生成
	void CreateCommandGenerator(DeviceContext::InstanceKey instanceKey_);
	//コマンドの生成
	void CreateCommands(DeviceContext::InstanceKey instanceKey_);

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



