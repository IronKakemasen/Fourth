#pragma once

class Nexus;
class DeviceContextCommandBehavior;
class DeviceContextDiplomat;

class DeviceContext
{
	//コアパーツを生成する
	class Setupper;

protected:

	//コアパーツにアクセスするのを許可するキー
	struct AccessKey;

public:

	//Nexusしか許さない
	struct NexusFieldProof;
	//コマンド生成キー
	struct GenerateKey;

	//他クラスにコアパーツを流用させないようにコマンドを生成して渡す
	class CommandProvider;
	//他クラスにコアパーツを流用させないようにコマンドを自ら実行する
	class CommandExecutor;

	std::unique_ptr<DeviceContextDiplomat> diplomat;

	DeviceContext(NexusFieldProof proof_);
	~DeviceContext();

private:

	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(NexusFieldProof proof_);
	//CommandProviderの生成
	std::unique_ptr<CommandProvider> InstantiateCommandProvider(NexusFieldProof proof_);
	//CommandExecutorの生成
	std::unique_ptr<CommandExecutor> InstantiateCommandExecutor(NexusFieldProof proof_);
};


//生成できるのはNexusのみ
struct DeviceContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
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



