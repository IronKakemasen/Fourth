#pragma once
#include "../DeviceContextCommandBehavior.h"
#include "../../../../External/DirectXTex/DirectXTex.h"


//リソースをアップロードするためのもの
struct CommandPrepareUpload : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandPrepareUpload(DeviceContext::GenerateKey generateKey_);

	void PrepareUpload
	(
		ID3D12Device8* device_,
		DirectX::ScratchImage const& image_,
		std::vector<D3D12_SUBRESOURCE_DATA>& subResources_
	);


};

