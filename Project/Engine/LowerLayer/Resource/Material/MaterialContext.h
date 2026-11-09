#pragma once

class Nexus;
class BufferContextDiplomat;

class MaterialContext
{
	//マテリアルに関するバッファを生成する
	class MaterialBufferCreator;
	//マテリアルのインデックスを割り当てる
	class MaterialIndexDispatcher;


public:

	struct NexusFieldProof;

	MaterialContext
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~MaterialContext();


private:

	std::unique_ptr<MaterialIndexDispatcher> materialIndexDispatcher;

};


struct MaterialContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};

