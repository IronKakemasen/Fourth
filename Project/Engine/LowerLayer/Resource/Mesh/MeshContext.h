#pragma once

class Nexus;
class BufferContextDiplomat;
class MeshContextDiplomat;

class MeshContext
{
public:
	//モデルを生成する。
	class ModelDataCreator;
	//モデルファイルからメッシュ情報を読み込む
	class ModelDataLoader;
	class ModelSlotAllocator;
	//代行者
	class ExecutionAgent;


	//自身の生成キー
	struct NexusFieldProof;
	//代行認証キー
	struct AgentKey;

	MeshContext(NexusFieldProof proof_, BufferContextDiplomat* bufferContextDiplomat_);
	~MeshContext();

	std::unique_ptr<MeshContextDiplomat> diplomat;

private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;

};

struct MeshContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct MeshContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};


