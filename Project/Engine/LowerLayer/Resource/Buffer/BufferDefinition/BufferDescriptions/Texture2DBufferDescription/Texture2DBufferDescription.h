#pragma once
#include "../BufferDescriptionBehavior.h"
#include "../../TextureType.h"


//外部
#include "../../../../../../../External/DirectXTex/DirectXTex.h"



//読み書き
struct Texture2DBufferDescription final :public BufferDescriptionBehavior, IAssembleShaderResource
{
	enum class TextureQuality
	{
		kLow		= 512,
		kMedium		= 1024,
		kHigh		= 2048,
		kUltra		= 0
	};

private:

	//いつかデバッグ用に使うかもと思い、一応、実体を作っとく
	struct Param
	{
		TextureType textureType;
		TextureQuality textureQuality;
	}param;

public:

	Texture2DBufferDescription
	(
		DirectX::ScratchImage scratchImage_,
		TextureType textureType_,
		TextureQuality textureQuality_
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
        uint32_t mipLevels =  1;
		bool isTextureQube{};

    }textureParams;

	void ExtractParams(DirectX::TexMetadata const& metaData_);

	DXGI_FORMAT FormatTable(TextureType type_)const;
};

