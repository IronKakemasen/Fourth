#pragma once
#include "../DeviceContextCommandBehavior.h"


//ルートシグネチャを生成するコマンド
struct CommandCreateRootSignature : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandCreateRootSignature(DeviceContext::GenerateKey generateKey_);
	~CommandCreateRootSignature();

	void CreateRootSignature
	(
		ID3D12Device8* device_,
		UINT nodeMask_,
		Microsoft::WRL::ComPtr<ID3DBlob>& signatureBlob_,
		ID3D12RootSignature** doublePtr_rootSignature_
	);
};

