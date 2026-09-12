#include "PreCompileHeader.h"
#include "TextureFileLoader.h"

//外部
#include "StringProcessing/StringProcessing.h"
#include "StringConverter/StringConverter.h"

namespace
{
	auto const fileName = "TextureFileLoader.cpp";
}


DirectX::ScratchImage TextureContext::TextureBufferCreator::TextureFileLoader::LoadTextureFile(std::string const filePath_, TextureComponent::TextureType textureType_)
{
	CheckExtension(filePath_);

	DirectX::ScratchImage image{};

	std::wstring filePathW = StringConverter::ConvertString(filePath_);
	HRESULT hr;

	///ddsファイルであれば（のみに変更）
	hr = DirectX::LoadFromDDSFile
	(
		filePathW.c_str(),
		DDS_FLAGS_Table(textureType_),
		nullptr,
		image
	);

	ErrorMessageOutput::Assert::DetectError
	(
		SUCCEEDED(hr),
		filePath_ + "このファイルの読み込みに失敗",
		fileName
	);

	Logger::Log("Load TextureFile: " + filePath_, fileName);

	return image;
}

void TextureContext::TextureBufferCreator::TextureFileLoader::CheckExtension(std::string const filePath_)
{
	if
	(
		!StringProcessing::CheckFileExtension(filePath_, ".dds") &&
		!StringProcessing::CheckFileExtension(filePath_, ".DDS") 
	)
	{
		ErrorMessageOutput::Assert::OutputError(filePath_ + "のファイル指定子がdds以外っす", fileName);
	}
}

DirectX::DDS_FLAGS TextureContext::TextureBufferCreator::TextureFileLoader::DDS_FLAGS_Table(TextureComponent::TextureType textureType_)
{
	static DirectX::DDS_FLAGS table[(UINT)TextureComponent::TextureType::kCount]
	{
		DirectX::DDS_FLAGS_NONE,
		DirectX::DDS_FLAGS_NONE,
		DirectX::DDS_FLAGS_NONE,
		DirectX::DDS_FLAGS_NONE
	};

	return table[(UINT)textureType_];

}
