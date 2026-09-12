#include "PreCompileHeader.h"
#include "TextureDataLoader.h"

//外部
#include "StringProcessing/StringProcessing.h"


namespace
{
	auto const fileName = "TextureDataLoader.cpp";
}

using namespace TextureComponent;

Texture2DState TextureContext::TextureBufferCreator::TextureDataLoader::LoadTextureState(std::string const key_)
{
	Texture2DState texture2DState;

	//keyからアンダーバーの先がテクスチャータイプ
	auto const textureTypeString = StringProcessing::SkipFetch(key_, '_');

	//文字列からenumに変換
	texture2DState.type = ToTextureType(textureTypeString);

	return texture2DState;
}


TextureType TextureContext::TextureBufferCreator::TextureDataLoader::ToTextureType(std::string const typeString_)
{
	TextureType type = TextureType::kCount;

	if		(typeString_ == DataStrings::kAlbedo)		type = TextureType::kAlbedo;
	else if (typeString_ == DataStrings::kEmissive)		type = TextureType::kEmissive;
	else if (typeString_ == DataStrings::kNormal)		type = TextureType::kNormal;
	else if (typeString_ == DataStrings::kSprite)		type = TextureType::kSprite;

	ErrorMessageOutput::Assert::DetectError
	(
		type != TextureType::kCount,
		typeString_ + ": そんなテクスチャタイプは設定されていない",
		fileName
	);

	return type;
}
