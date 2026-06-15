#pragma once

class WinApp;
class DeviceContextCommandBehavior;


class DeviceContext
{
public:

	enum CommandType
	{
		//GPUリソース生成
		kCreateGPUBuffer,
		//DescriptorHeapを作成
		kCreateDescriptorHeap,
		//Resourceのビューを作成
		kCreateResourceView,


		kCount
	};
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

	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandProviderの生成
	void CreateCommandProvider(DeviceContext::InstanceKey instanceKey_);
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



