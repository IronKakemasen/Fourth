#pragma once
#include "../TextureBufferCreator.h"
#include "../../../BufferDefinition/TextureComponent.h"


class BufferContext::TextureBufferCreator::TextureDataLoader
{
	friend class BufferContext::TextureBufferCreator;

	struct DataStrings
	{
		static inline const std::string kJsonFile		= "TextureSettings";

		static inline const std::string	kQuality		= "Quality";
		static inline const std::string	kQualityLow		= "Low";
		static inline const std::string kQualityMidium	= "Mid";
		static inline const std::string kQualityHigh	= "High";
		static inline const std::string kQualityUltra	= "Ultra";

		static inline const std::string	kAlbedo			= "albedo";
		static inline const std::string kNormal			= "normal";
		static inline const std::string kEmissive		= "emissive";
		static inline const std::string kSprite			= "sprite";
	};


	///レジストリーに登録されている全てのテクスチャファイルの、
	///Texture2DBufferDescriptionを構成する要素があるジェーソンファイルからデータを読む
	static std::map<std::string, Texture2DState> LoadAll();


	//以下ヘルパー
private:

	static TextureComponent::TextureType ToTextureType(std::string const typeString_);
	static TextureComponent::TextureQuality ToTextureQuality(std::string const qualityString_);
	
};

