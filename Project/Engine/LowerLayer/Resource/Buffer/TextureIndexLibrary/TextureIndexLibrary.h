#pragma once
#include "../BufferContext.h"

class BufferContext::TextureIndexLibrary
{
public:
	TextureIndexLibrary(NexusFieldProof proof_);

	void Import(NexusFieldProof proof_,std::string const name_, SRVHeapIndex const index_);
	SRVHeapIndex Export(std::string const name_)const;

private:

	std::unordered_map<std::string, SRVHeapIndex> data;
};

