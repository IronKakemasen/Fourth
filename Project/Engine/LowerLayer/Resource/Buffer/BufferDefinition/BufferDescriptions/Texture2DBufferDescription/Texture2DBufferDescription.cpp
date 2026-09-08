#include "PreCompileHeader.h"
#include "Texture2DBufferDescription.h"

namespace 
{
    auto const fileName = "Texture2DBufferDescription.cpp";
}

using namespace TextureComponent;

Texture2DBufferDescription::Texture2DBufferDescription
(
	DirectX::ScratchImage scratchImage_,
	TextureType textureType_,
	TextureQuality textureQuality_
):BufferDescriptionBehavior(D3D12_RESOURCE_STATE_COPY_DEST, ProjectConfig::Render::NumBuffer::kSingleBuffer)
{
    param.texture2DState.type = textureType_;
    param.texture2DState.quality = textureQuality_;

    //メタデータから必要情報を抽出
    auto const& metaData = scratchImage_.GetMetadata();
    ExtractParams(metaData);
}

//パラーメーターチェック
void Texture2DBufferDescription::CheckRequirementsFilled() const
{

}

//リソースディスクの生成
D3D12_RESOURCE_DESC Texture2DBufferDescription::CreateResourceDesc()const
{
    D3D12_RESOURCE_DESC resourceDesc{};
	
	resourceDesc.Width = textureParams.width;
	resourceDesc.Height = textureParams.height;
	//Mipmapの数
	resourceDesc.MipLevels = UINT16(textureParams.mipLevels);
	//TextureのFormat
	resourceDesc.Format = textureParams.format;
	
    ///2Dテクスチャなので以下は固定
    //サンプリングカウント
	resourceDesc.SampleDesc.Count = 1;
    //Textureの次元数
    resourceDesc.DepthOrArraySize = textureParams.isTextureQube ? 6 : 1;	
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    
    return resourceDesc;

}

//ヒーププロパティの生成
D3D12_HEAP_PROPERTIES Texture2DBufferDescription::CreateHeapProperties()const
{
    D3D12_HEAP_PROPERTIES heapProps{};
    heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

    return heapProps;
}

//SRVDesc生成
D3D12_SHADER_RESOURCE_VIEW_DESC Texture2DBufferDescription::CreateSRV_Desc()const
{
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

    //共通設定
    // TextureのFormat
    srvDesc.Format = textureParams.format;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

    //キューブマップかどうかで分岐
    if (textureParams.isTextureQube)
    {
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;

        //一番細かいMipから使用
        srvDesc.TextureCube.MostDetailedMip = 0;
        //MipMap数
        srvDesc.TextureCube.MipLevels = textureParams.mipLevels;
        //MipMapのLOD Clamp
        srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;

    }
    else
    {
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        //MipMap数
        srvDesc.Texture2D.MipLevels = textureParams.mipLevels;
        //Plane
        srvDesc.Texture2D.PlaneSlice = 0;
        //一番細かいMipから使用
        srvDesc.Texture2D.MostDetailedMip = 0;
        // MipMapのLOD Clamp
        srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
    }
    return srvDesc;
}

DXGI_FORMAT Texture2DBufferDescription::FormatTable(TextureType type_)const
{
    //ほぼないだろうが一応ね
    ErrorMessageOutput::Assert::DetectError(type_ != TextureType::kCount , "kCountを指定", fileName);

    static DXGI_FORMAT table[UINT(TextureType::kCount)]
    {
        DXGI_FORMAT_BC7_UNORM_SRGB,
        DXGI_FORMAT_BC5_UNORM,
        DXGI_FORMAT_BC7_UNORM_SRGB,
        DXGI_FORMAT_BC7_UNORM_SRGB
    };

    return table[UINT(type_)];
}


void Texture2DBufferDescription::ExtractParams(DirectX::TexMetadata const& metaData_)
{
    //キューブマップかどうか
    textureParams.isTextureQube = metaData_.IsCubemap();

    //TextureTypeによるフォーマット
    textureParams.format = FormatTable(param.texture2DState.type);

    //TextureQualityによる最大解像度
    float maxResolution = float(param.texture2DState.quality);

    //出力解像度
    float srcWidth = float(metaData_.width);
    float srcHeight = float(metaData_.height);

    textureParams.width = uint32_t(srcWidth);
    textureParams.height = uint32_t(srcHeight);

    //最大解像度を設定せず、画像ファイルのありのままの姿ならスルー
    if (maxResolution > (float)TextureQuality::kUltra)
    {
        //縦横のうちデカいほうのサイズ
        float const maxSize = Comparison::Max(srcWidth, srcHeight);

        //それが最大解像度を超えていたら縮小しなくてはいけない
        if (maxSize > maxResolution)
        {
            //maxSizeをmaxResolutionに合わせるためのスケール
            float const adjustScale = maxResolution / maxSize;

            textureParams.width = uint32_t(srcWidth * adjustScale);
            textureParams.height = uint32_t(srcHeight * adjustScale);
        }
    }

    //Spriteはmipmapを生成しない
    if (param.texture2DState.type == TextureType::kSprite) return;

    //通常テクスチャはmipmapを生成
    uint32_t const maxDimension = Comparison::Max(textureParams.width, textureParams.height);
    //何枚の縮小画像を用意するか計算
    for (uint32_t size = maxDimension; size > 1; size /= 2)
    {
        ++textureParams.mipLevels;
    }

}