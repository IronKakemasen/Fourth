#pragma once
#include "../TextureBufferCreator.h"
#include "../../../BufferDefinition/TextureType.h"


class BufferContext::TextureBufferCreator::TextureLoader
{
	friend class BufferContext::TextureBufferCreator;

	struct DataStrings
	{
		static inline const std::string kJsonFileName	= "TextureSettings";

		static inline const std::string kQualityLow		= "Low";
		static inline const std::string kQualityMidium	= "Mid";
		static inline const std::string kQualityHigh	= "High";
		static inline const std::string kQualityUltra	= "Ultra";
		
		static inline const std::string kAlbedo			= "albedo";
		static inline const std::string kNormal			= "normal";
		static inline const std::string kEmissive		= "emissive";
		static inline const std::string kSprite			= "sprite";
	};


	TextureType ToTextureType(std::string const typeString_);

};

