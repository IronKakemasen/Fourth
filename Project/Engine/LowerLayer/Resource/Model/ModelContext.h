#pragma once

class Nexus;
class BufferContextDiplomat;
class ModelContextDiplomat;

///tesutooooooooooooooooooooooooooooooooooo
struct TestModelOKIBA;

class ModelContext
{
	//モデルファイルからモデル情報を読み込む
	class ModelDataLoader;

public:
	//モデルレジストリーファイルにあるモデルデータのバッファを生成する。
	class ModelDataCreator;
	//インスタンス化されたモデルクラスのモデルファイル名をもとに中身を構築してあげる
	class ModelDescAssembler;
	///モデルクラスを生成する
	class ModelCreator;
	//モデルのコンテナ
	class ModelContainer;
	class ModelSlotAllocator;

	//代行者
	class ExecutionAgent;
	class ToolLender;

	//ネクサスフィールド証明
	struct NexusFieldProof;
	//代行認証キー
	struct AgentKey;

	ModelContext(NexusFieldProof proof_, BufferContextDiplomat* bufferContextDiplomat_);
	~ModelContext();

	//外交官
	std::unique_ptr<ModelContextDiplomat> diplomat;
	std::unique_ptr<ModelCreator> modelCreator;

private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;
	std::unique_ptr<ModelContainer> modelContainer;
	std::unique_ptr<TestModelOKIBA> testModelOKIBA;
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


