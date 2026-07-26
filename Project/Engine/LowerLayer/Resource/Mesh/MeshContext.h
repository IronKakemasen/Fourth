#pragma once

class Nexus;
class BufferContextDiplomat;
class MeshContextDiplomat;

class MeshContext
{
	//モデルファイルからモデル情報を読み込む
	class ModelDataLoader;
	class ModelSlotAllocator;

public:
	//モデルレジストリーファイルにあるモデルのバッファを生成する。
	class ModelDataCreator;
	//インスタンス化されたモデルクラスのモデルファイル名をもとに中身を構築してあげる
	class ModelAssembler;

	//代行者
	class ExecutionAgent;

	//自身の生成キー
	struct NexusFieldProof;
	//代行認証キー
	struct AgentKey;

	MeshContext(NexusFieldProof proof_, BufferContextDiplomat* bufferContextDiplomat_);
	~MeshContext();

	//外交官
	std::unique_ptr<MeshContextDiplomat> diplomat;

private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;
	std::unique_ptr<ModelAssembler> modelAssembler;

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


