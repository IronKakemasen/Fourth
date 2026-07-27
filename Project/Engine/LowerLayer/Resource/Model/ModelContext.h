#pragma once

class Nexus;
class BufferContextDiplomat;
class MeshContextDiplomat;

class ModelContext
{
	//モデルファイルからモデル情報を読み込む
	class ModelDataLoader;
	class ModelSlotAllocator;

public:
	//モデルレジストリーファイルにあるモデルデータのバッファを生成する。
	class ModelDataCreator;
	//インスタンス化されたモデルクラスのモデルファイル名をもとに中身を構築してあげる
	class ModelDescAssembler;
	///モデルクラスを生成する
	class ModelCreator;
	//モデルのコンテナ
	class ModelContainer;

	//代行者
	class ExecutionAgent;

	//ネクサスフィールド証明
	struct NexusFieldProof;
	//代行認証キー
	struct AgentKey;

	ModelContext(NexusFieldProof proof_, BufferContextDiplomat* bufferContextDiplomat_);
	~ModelContext();

	//外交官
	std::unique_ptr<MeshContextDiplomat> diplomat;

private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;
	std::unique_ptr<ModelCreator> modelCreator;
	std::unique_ptr<ModelContainer> modelContainer;

};

struct ModelContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

struct ModelContext::AgentKey
{
private:

	friend class ExecutionAgent;
	explicit AgentKey() = default;
};


