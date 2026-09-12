#pragma once

class Nexus;
class BufferContextDiplomat;


class TextureContext
{
public:

	//ネクサスフィールドの証
	struct NexusFieldProof;

	TextureContext
	(
		NexusFieldProof proof_, 
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~TextureContext();

private:


};


struct TextureContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

