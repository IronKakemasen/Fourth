#include "PreCompileHeader.h"
#include "TextureFileLoader.h"

//外部
#include "StringProcessing/StringProcessing.h"
#include "StringConverter/StringConverter.h"

namespace
{
	auto const fileName = "TextureFileLoader.cpp";
}


DirectX::ScratchImage BufferContext::TextureBufferCreator::TextureFileLoader::LoadTextureFile(std::string const filePath_, TextureComponent::TextureType textureType_)
{
	CheckExtension(filePath_);

	DirectX::ScratchImage image{};

	std::wstring filePathW = StringConverter::ConvertString(filePath_);
	HRESULT hr;

	///ddsファイルであれば
	if
	(
		StringProcessing::CheckFileExtension(filePath_, ".dds") ||
		StringProcessing::CheckFileExtension(filePath_, ".DDS")
	)
	{
		hr = DirectX::LoadFromDDSFile
		(
			filePathW.c_str(),
			DDS_FLAGS_Table(textureType_),
			nullptr,
			image
		);

	}
	///そうでなければ
	else
	{
		hr = DirectX::LoadFromWICFile
		(
			filePathW.c_str(),
			WIC_FLAGS_Table(textureType_),
			nullptr,
			image
		);
	}

	ErrorMessageOutput::Assert::DetectError
	(
		SUCCEEDED(hr),
		filePath_ + "このファイルの読み込みに失敗",
		fileName
	);

	Logger::Log("Load TextureFile: " + filePath_, fileName);
	Logger::Log("\n");

	return image;
}

void BufferContext::TextureBufferCreator::TextureFileLoader::CheckExtension(std::string const filePath_)
{
	if
	(
		!StringProcessing::CheckFileExtension(filePath_, ".dds") &&
		!StringProcessing::CheckFileExtension(filePath_, ".DDS") &&
		!StringProcessing::CheckFileExtension(filePath_, ".png") &&
		!StringProcessing::CheckFileExtension(filePath_, ".jpg")
	)
	{
		ErrorMessageOutput::Assert::OutputError(filePath_ + "のファイル指定子おかしいっす", fileName);
	}
}

DirectX::WIC_FLAGS BufferContext::TextureBufferCreator::TextureFileLoader::WIC_FLAGS_Table(TextureComponent::TextureType textureType_)
{
	static DirectX::WIC_FLAGS table[(UINT)TextureComponent::TextureType::kCount]
	{
		DirectX::WIC_FLAGS_FORCE_SRGB,
		DirectX::WIC_FLAGS_IGNORE_SRGB,
		DirectX::WIC_FLAGS_FORCE_SRGB,
		DirectX::WIC_FLAGS_FORCE_SRGB
	};

	return table[(UINT)textureType_];
}

DirectX::DDS_FLAGS BufferContext::TextureBufferCreator::TextureFileLoader::DDS_FLAGS_Table(TextureComponent::TextureType textureType_)
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
