#pragma once
#include "../BufferDescriptionBehavior.h"
#include "../../TextureComponent.h"


//外部
#include "../../../../../../External/DirectXTex/DirectXTex.h"



//読み書き
struct Texture2DBufferDescription final :public BufferDescriptionBehavior, IAssembleShaderResource
{

private:

	//いつかデバッグ用に使うかもと思い、一応、実体を作っとく
	struct Param
	{
		Texture2DState texture2DState;

	}param;

public:

	Texture2DBufferDescription
	(
		DirectX::ScratchImage& scratchImage_,
		Texture2DState texture2DState_
	);

	//パラーメーターチェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//SRVDesc生成
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const override;


private:

    struct TextureParams
    {
		DXGI_FORMAT format{};
		uint32_t width{};
		uint32_t height{};
        size_t mipLevels =  1;
		bool isTextureQube{};

    }textureParams;

	void ExtractParams(DirectX::TexMetadata const& metaData_);

	DXGI_FORMAT FormatTable(TextureComponent::TextureType type_)const;
};

