#include "PreCompileHeader.h"
#include "TextureIndexLibrary.h"

BufferContext::TextureIndexLibrary::TextureIndexLibrary(NexusFieldProof proof_)
{

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
		"TextureIndexLibrary.cpp"
	);

	return data.at(name_);
}
