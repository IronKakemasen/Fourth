#pragma once

class Nexus;
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
		//SwapChain生成
		kStructureSwapChain,


		kCount
	};

	//生成キー。Nexusしか許さない
	struct InstanceKey;
	
	//コアパーツにアクセスするのを許可するキー
	struct AccessKey;

	//CommandProvider.他クラスにコアパーツを流用させないようにコマンドを生成して渡す
	class CommandProvider;
	std::unique_ptr<CommandProvider> commandProvider;

	DeviceContext(InstanceKey instanceKey);
	~DeviceContext();

	//DescriptorHeapのハンドルインクリメントサイズを返す関数
	UINT CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE type_);

private:

	//コアパーツを生成する
	class Setupper;

	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandProviderの生成
	void CreateCommandProvider(DeviceContext::InstanceKey instanceKey_);
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
	explicit AccessKey() = default;
};



