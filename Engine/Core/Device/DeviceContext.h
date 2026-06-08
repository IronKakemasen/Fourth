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
		kCreateGPUBuffer,
		//DescriptorHeapを作成
		kCreateDescriptorHeap,


		kCount
	};

	//コマンド生成クラス
	class CommandGenerator;
	//生成キー。WinAppしか許さない
	struct InstanceKey;
	//デバイスにアクセスするのを許可するキー
	struct DeviceAccessKey;
	//CommandProvider
	class CommandProvider;
	std::unique_ptr<CommandProvider> commandProvider;

	DeviceContext(InstanceKey instanceKey);
	~DeviceContext();

	//DescriptorHeapのハンドルインクリメントサイズを返す関数
	UINT PassDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_);

private:

	//Setupper
	class Setupper;

	using CommandList = std::vector<std::unique_ptr<DeviceContextCommandBehavior>>;
	using CommandMap = std::unordered_map<CommandType, CommandList>;

	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;

	std::unique_ptr<CommandGenerator> commandGenerator;

	//コマンドのコンテナ
	CommandMap commandContainer;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandProviderの生成
	void CreateCommandProvider(DeviceContext::InstanceKey instanceKey_);
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

	friend class CommandProvider;
	explicit DeviceAccessKey() = default;
};



