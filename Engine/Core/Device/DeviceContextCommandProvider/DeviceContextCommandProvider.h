#pragma once
#include "../DeviceContext.h"


struct ConstantBufferDescription;
struct ColorBufferDescription;
class CreatingGPUBuffer;

//Deviceを使用する処理を、使用しない形にコマンド化して提供するクラス
class DeviceContext::CommandProvider
{
public:

	CommandProvider(DeviceContext::InstanceKey instanceKey_, 
		std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> func_ , CommandMap* commandContainer_);
	
	//定数バッファを生成するコマンドを返す関数
	[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)> GetCreateConstantBufferCommmand();
	//カラーバッファを生成するコマンドを返す関数
	[[nodiscard]] std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)> GetCreateColorBufferCommmand();

private:

	//デバイスにアクセスする関数
	std::function< ID3D12Device8* (DeviceContext::DeviceAccessKey)> deviceGetter;
	//コマンドのコンテナ
	CommandMap* commandContainer;

};





