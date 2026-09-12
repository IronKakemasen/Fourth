#include "PreCompileHeader.h"
#include "TextureIndexLibrary.h"

BufferContext::TextureIndexLibrary::TextureIndexLibrary(NexusFieldProof proof_)
{

}

namespace
{
	auto const fileName = "TextureIndexLibrary.cpp";
}

void BufferContext::TextureIndexLibrary::Import(NexusFieldProof proof_, std::string const name_, SRVHeapIndex const index_)
{
	data[name_] = index_;
}

SRVHeapIndex BufferContext::TextureIndexLibrary::Export(std::string const name_)const
{
	ErrorMessageOutput::Assert::DetectError
	(
		data.find(name_) != data.end(),
		name_ + "こんなテクスチャインデックスは管理してまへん",
		fileName
	);

	return data.at(name_);
}

void BufferContext::TextureIndexLibrary::Log()
{
	std::string log = "\n- - - - - - - - - - TextureIndexLibrary - - - - - - - - - -\n\n";

	for (auto const& [key, value] : data)
	{
		log += key + "[" + std::to_string(value) + "]\n";
	}

	log += "\n- - - - - - - - - - - - - - - - - - - -";
	Logger::Log(log);
	Logger::Log("", fileName);

}
