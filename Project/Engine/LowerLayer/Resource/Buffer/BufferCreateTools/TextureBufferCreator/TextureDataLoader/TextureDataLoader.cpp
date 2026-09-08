#include "PreCompileHeader.h"
#include "TextureDataLoader.h"

//外部
#include "StringProcessing/StringProcessing.h"


namespace
{
	auto const fileName = "TextureDataLoader.cpp";
}

using namespace TextureComponent;

Texture2DState BufferContext::TextureBufferCreator::TextureDataLoader::LoadTextureState(std::string const key_)
{
	Texture2DState texture2DState;

	auto* miyaJison = Miyajison::Get();

	//keyからアンダーバーの先がテクスチャータイプ
	auto const textureTypeString = StringProcessing::SkipFetch(key_, '_');
	//クォリティは、まあそのまま読み込む
	auto const qualityString = miyaJison->LoadData<std::string>(DataStrings::kJsonFile, { key_ , DataStrings::kQuality });

	Logger::Log("TextureState: " + key_ + "{ " + textureTypeString + "," + qualityString + " }");

	//文字列からenumに変換
	texture2DState.type = ToTextureType(textureTypeString);
	texture2DState.quality = ToTextureQuality(qualityString);

	return texture2DState;
}


TextureType BufferContext::TextureBufferCreator::TextureDataLoader::ToTextureType(std::string const typeString_)
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

TextureComponent::TextureQuality BufferContext::TextureBufferCreator::TextureDataLoader::ToTextureQuality(std::string const qualityString_)
{
	TextureQuality type = TextureQuality::kCount;

	if (qualityString_ == DataStrings::kQualityLow)			type = TextureQuality::kLow;
	else if (qualityString_ == DataStrings::kQualityMidium)	type = TextureQuality::kMedium;
	else if (qualityString_ == DataStrings::kQualityHigh)	type = TextureQuality::kHigh;
	else if (qualityString_ == DataStrings::kQualityUltra)	type = TextureQuality::kUltra;

	ErrorMessageOutput::Assert::DetectError
	(
		type != TextureQuality::kCount,
		qualityString_ + ": そんなクォリティタイプは設定されていない",
		fileName
	);

	return type;

}
