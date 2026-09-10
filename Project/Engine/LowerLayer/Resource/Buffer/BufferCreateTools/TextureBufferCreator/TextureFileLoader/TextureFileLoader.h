#pragma once
#include "../TextureBufferCreator.h"
#include "../../../BufferDefinition/TextureComponent.h"

//外部
#include "../../../../../../../External/DirectXTex/DirectXTex.h"


class BufferContext::TextureBufferCreator::TextureFileLoader
{
	friend class TextureBufferCreator;

	static DirectX::ScratchImage LoadTextureFile(std::string const filePath_, TextureComponent::TextureType textureType_);

	//以下ヘルパー
private:
	//念のためのファイル指定子チェック
	static void CheckExtension(std::string const filePath_);
	//textureType別にWIC_FLAGSを設定したテーブル
	static DirectX::WIC_FLAGS WIC_FLAGS_Table(TextureComponent::TextureType textureType_);
	//そのDDS版
	static DirectX::DDS_FLAGS DDS_FLAGS_Table(TextureComponent::TextureType textureType_);

};

