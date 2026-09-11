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

}

struct Texture2DState
{
	TextureComponent::TextureType type = TextureComponent::TextureType::kCount;
};

