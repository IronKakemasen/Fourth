#pragma once

class Nexus;
class BufferContextDiplomat;

class MaterialContext
{
	//マテリアルに関するバッファを生成する
	class MaterialBufferCreator;
	//マテリアルのインデックスを割り当てる
	class MaterialIndexDispatcher;
	//マテリアルデータをバッファへ書き込みます
	class MaterialDataBatcher;

public:

	//描画対象にマテリアルをアタッチする
	class MaterialAttacher;
	class ExecutionAgent;


	struct NexusFieldProof;
	struct AgentKey;

	MaterialContext
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	~MaterialContext();


private:

	std::unique_ptr<MaterialIndexDispatcher> materialIndexDispatcher;
	std::unique_ptr<MaterialAttacher> materialAttacher;
	std::unique_ptr<MaterialDataBatcher> materialDataBatcher;

};


struct MaterialContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;

};

struct MaterialContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;

};


