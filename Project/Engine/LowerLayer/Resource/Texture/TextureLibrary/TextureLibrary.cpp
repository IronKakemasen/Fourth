#include "PreCompileHeader.h"
#include "TextureLibrary.h"


//外部
#include "RegistryLoader/RegistryLoader.h"

TextureContext::TextureLibrary::TextureLibrary(NexusFieldProof proof_)
{

}

namespace
{
	auto const fileName = "TextureLibrary.cpp";
}

void TextureContext::TextureLibrary::Import(NexusFieldProof proof_, std::string const name_, SRVHeapIndex const index_)
{
	data[name_] = index_;
}

SRVHeapIndex TextureContext::TextureLibrary::Export(std::string const name_)const
{
	std::string actualName = name_;

	//まずリスト内に存在しているかチェック
	if (data.find(name_) == data.end())
	{
		//もしかしたら、引数がパスの可能性もあるので、その場合はパス→名前変換
		actualName = RegistryLoader::ValueToKey<RegistryLoader::RegistryFileType::kTextureFiles>(name_);
	}

	ErrorMessageOutput::Assert::DetectError
	(
		data.find(actualName) != data.end(),
		actualName + "こんなテクスチャインデックスは管理してまへん",
		fileName
	);

	return data.at(actualName);
}

void TextureContext::TextureLibrary::Log()
{
	std::string log = "\n- - - - - - - - - - TextureLibrary - - - - - - - - - -\n\n";

	for (auto const& [key, value] : data)
	{
		log += key + "[" + std::to_string(value) + "]\n";
	}

	log += "\n- - - - - - - - - - - - - - - - - - - -";
	Logger::Log(log);
	Logger::Log("", fileName);

}
