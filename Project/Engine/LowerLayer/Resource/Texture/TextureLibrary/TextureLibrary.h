#pragma once
#include "../TextureContext.h"

//外部
#include "../../../Buffer/BufferDefinition/TextureComponent.h"

class TextureContext::TextureLibrary
{
public:

	TextureLibrary(NexusFieldProof proof_);

	void Import(NexusFieldProof proof_, std::string const name_, SRVHeapIndex const index_);
	SRVHeapIndex Export(std::string const name_)const;

	//中身確認用
	void Log();

private:

	std::unordered_map<std::string, SRVHeapIndex> data;

};

