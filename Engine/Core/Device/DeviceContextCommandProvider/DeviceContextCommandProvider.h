#pragma once
#include "../DeviceContext.h"

class DeviceContextCommandBehavior;

//Deviceを使用する処理を、使用しない形にコマンド化して提供するクラス
//初期化生成しか使用しないかつ引数がほぼない場合は、自らコマンドをたたく
class DeviceContext::CommandProvider
{
public:

	//コマンド生成キー
	struct GenerateKey;

	CommandProvider
	(
		DeviceContext::InstanceKey instanceKey_, 
		std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter_,
		std::function< IDXGIFactory7* (DeviceContext::AccessKey)> dxgiFactoryGetter_
	);
	
	//リソースを生成するコマンドを返す関数(ConstantBufferDescription , ColorBufferDescription)
	[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>
	(
		const D3D12_RESOURCE_DESC& resourceDesc_,
		const D3D12_HEAP_PROPERTIES& heapProperties_,
		const D3D12_CLEAR_VALUE* clearValue_,
		D3D12_RESOURCE_STATES initialState_,
		const std::string& name_
	)>
	ProvideCreateResourceCommand();

	//DescriptorHeapを生成するコマンドを返す関数
	[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE , UINT , bool )>
		ProvideCreateDescriptorHeapCommand();

	//リソースのViewを作成するコマンドを返す関数
	template<typename ViewType>
	[[nodiscard]] std::function<void(ID3D12Resource* resource_, const ViewType* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_)>
		ProvideCreateViewCommand();

	//UAV作成コマンドのみ引数が異なるため別途用意
	[[nodiscard]] std::function<void(ID3D12Resource* resource_, const D3D12_UNORDERED_ACCESS_VIEW_DESC* desc_, D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU_, ID3D12Resource* CounterResource_)>
		ProvideCreateUAVCommand();
	
	//スワップチェーンを生成するためのコマンド
	[[nodiscard]] std::function< HRESULT
	(
		ID3D12CommandQueue* commandQueue_,
		DXGI_SWAP_CHAIN_DESC1 desc_,
		IDXGISwapChain4** swapChainDoublePtr_,
		const HWND hWnd_
	)> ProvideCreateSwapChainCommand();

	//CommandContextのコアパーツ生成関数
	[[nodiscard]] std::tuple
	<
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>,
		std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, ProjectConfig::Render::kRequiredGPUBufferSum>,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList6>
	>
	CreateCommandContextCoreParts(DeviceContext::InstanceKey instanceKey_);


private:

	//デバイスにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::AccessKey)> deviceGetter;
	std::function< IDXGIFactory7* (DeviceContext::AccessKey)> dxgiFactoryGetter;

};




struct DeviceContext::CommandProvider::GenerateKey
{
private:

	friend class DeviceContext::CommandProvider;
	explicit GenerateKey() = default;
};

