#include "PreCompileHeader.h"
#include "TextureDataLoader.h"


#include "RegistryLoader/RegistryLoader.h"
#include "StringProcessing/StringProcessing.h"


namespace
{
	auto const fileName = "TextureDataLoader.cpp";
}

using namespace TextureComponent;

std::map<std::string, Texture2DState> BufferContext::TextureBufferCreator::TextureDataLoader::LoadAll()
{
	std::map<std::string, Texture2DState> texture2DStateMap;

	auto* miyaJison = Miyajison::Get();

	Logger::Log("Load textureData Starts",fileName);

	//Registryに登録されているテクスチャファイルのキーを走査する
	auto const allKeys = RegistryLoader::LoadRegistryKeys<RegistryLoader::RegistryFileType::kTextureFiles>();
	for (auto const& key : allKeys)
	{

		//keyからアンダーバーの先がテクスチャータイプ
		auto const textureTypeString = StringProcessing::SkipFetch(key, '_');
		//クォリティは、まあそのまま読み込む
		auto const qualityString = miyaJison->LoadData<std::string>(DataStrings::kJsonFile, { key , DataStrings::kQuality });

		Logger::Log("Load: " + key + "{ " + textureTypeString + "," + qualityString + " }");

		//文字列からenumに変換
		texture2DStateMap[key].type = ToTextureType(textureTypeString);
		texture2DStateMap[key].quality = ToTextureQuality(qualityString);
	}

	return texture2DStateMap;
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
