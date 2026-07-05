#pragma once

class Nexus;
class DeviceContextCommandBehavior;


class DeviceContext
{
	//コアパーツを生成する
	class Setupper;

public:

	//自身の生成キー。Nexusしか許さない
	struct InstanceKey;
	//コアパーツにアクセスするのを許可するキー
	struct AccessKey;
	//コマンド生成キー
	struct GenerateKey;

	//他クラスにコアパーツを流用させないようにコマンドを生成して渡す
	class CommandProvider;
	//他クラスにコアパーツを流用させないようにコマンドを自ら実行する
	class CommandExecutor;

	std::unique_ptr<CommandProvider> commandProvider;
	std::unique_ptr<CommandExecutor> commandExecutor;

	DeviceContext(InstanceKey instanceKey);
	~DeviceContext();

private:

	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandProviderの生成
	void CreateCommandProvider(DeviceContext::InstanceKey instanceKey_);
	//CommandExecutorの生成
	void CreateCommandExecutor(DeviceContext::InstanceKey instanceKey_);
};


//生成できるのはNexusのみ
struct DeviceContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};


//アクセスさせるがポインタは渡さん
struct DeviceContext::AccessKey
{
private:

	friend class CommandProvider;
	friend class CommandExecutor;

	explicit AccessKey() = default;
};

struct DeviceContext::GenerateKey
{
private:

	friend class DeviceContext::CommandProvider;
	friend class DeviceContext::CommandExecutor;

	explicit GenerateKey() = default;
};



