#pragma once

namespace TextureComponent
{
	enum class TextureType
	{
		kAlbedo,
		kNormal,
		kEmissive,
		kSprite,
		kCount
	};

	enum class TextureQuality
	{
		kLow	= 512,
		kMedium	= 1024,
		kHigh	= 2048,
		kUltra	= 0,
		kCount	= 99999999
	};
}

struct Texture2DState
{
	TextureComponent::TextureType type = TextureComponent::TextureType::kCount;
	TextureComponent::TextureQuality quality = TextureComponent::TextureQuality::kCount;
};

