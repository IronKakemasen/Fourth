#pragma once
#include "../DeviceContextCommandBehavior.h"
#include "../../../../External/DirectXTex/DirectXTex.h"


//リソースをアップロードするためのもの
struct CommandUploadResource : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandUploadResource(DeviceContext::GenerateKey generateKey_);

	void UploadTextureResource
	(
		ID3D12Device8* device_,
		DirectX::ScratchImage const& image_,
		std::vector<D3D12_SUBRESOURCE_DATA>& subResources_
	);


};

