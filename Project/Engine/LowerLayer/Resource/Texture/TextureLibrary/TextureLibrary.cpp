#include "PreCompileHeader.h"
#include "TextureLibrary.h"

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
	ErrorMessageOutput::Assert::DetectError
	(
		data.find(name_) != data.end(),
		name_ + "こんなテクスチャインデックスは管理してまへん",
		fileName
	);

	return data.at(name_);
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
