#pragma once
#include "../DeviceContext.h"


struct ConstantBufferDescription;
struct ColorBufferDescription;
struct CommandCreateGPUBuffer;
struct CommandCreateDescriptorHeap;

//Deviceを使用する処理を、使用しない形にコマンド化して提供するクラス
class DeviceContext::CommandProvider
{
public:

	CommandProvider(DeviceContext::InstanceKey instanceKey_, 
		std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_ , CommandMap* commandContainer_);
	
	//バッファを生成するコマンドを返す関数(ConstantBufferDescription , ColorBufferDescription)
	template <typename DescriptionType>
	[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const DescriptionType&)> PassCreateBufferCommand();

	//DescriptorHeapを生成するコマンドを返す関数
	[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>(D3D12_DESCRIPTOR_HEAP_TYPE , UINT , bool )> PassCreateDescriptorHeapCommand();


private:

	//デバイスにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> deviceGetter;
	//コマンドのコンテナ
	CommandMap* commandContainer;

};





