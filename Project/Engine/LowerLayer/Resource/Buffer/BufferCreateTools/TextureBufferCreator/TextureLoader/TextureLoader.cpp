#include "PreCompileHeader.h"
#include "TextureLoader.h"

namespace
{
	auto const fileName = "TextureLoader.cpp";
}


TextureType BufferContext::TextureBufferCreator::TextureLoader::ToTextureType(std::string const typeString_)
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