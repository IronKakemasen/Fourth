#pragma once
#include "../TextureBufferCreator.h"

//外部
#include "../../../../Buffer/BufferDefinition/TextureComponent.h"
#include "../../../../../../External/DirectXTex/DirectXTex.h"


class TextureContext::TextureBufferCreator::TextureFileLoader
{
	friend class TextureBufferCreator;

	static DirectX::ScratchImage LoadTextureFile(std::string const filePath_, TextureComponent::TextureType textureType_);

	//以下ヘルパー
private:
	//念のためのファイル指定子チェック
	static void CheckExtension(std::string const filePath_);
	//textureType別のDDS_FLAGSテーブル
	static DirectX::DDS_FLAGS DDS_FLAGS_Table(TextureComponent::TextureType textureType_);

};

