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
	//モデルのコンテナ。おそらくただのコンテナになると思う
	class ModelContainer;
	//TransformMatrixSlotの空きインデックスを割り当てたり、モデル名をもとに
	//モデルデータの割り当てを行う
	class ModelSlotAllocator;
	//インスタンス化されたモデルクラスのモデルファイル名をもとに中身を構築してあげる
	class ModelDescAssembler;

public:
	//全てのモデルファイルのモデルデータのバッファを生成する。
	class ModelDataCreator;
	///モデルクラスを生成する
	class ModelCreator;
	//モデルの書き込まなくてはならないデータ(TransformMatrixなど)のバッチングを行う
	class ModelDataBatcher;

	//代行者
	class ExecutionAgent;
	//コマンド提供者
	class CommandProvider;
	class ToolLender;

	//ネクサスフィールド証明
	struct NexusFieldProof;
	//代行認証キー
	struct AgentKey;
	//コマンド提供者キー
	struct ProviderKey;


	ModelContext(NexusFieldProof proof_, BufferContextDiplomat* bufferContextDiplomat_);
	~ModelContext();

	//外交官
	std::unique_ptr<ModelContextDiplomat> diplomat;

private:


	std::unique_ptr<ModelDataCreator> modelDataCreator;
	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;
	std::unique_ptr<ModelContainer> modelContainer;
	std::unique_ptr<ModelCreator> modelCreator;
	std::unique_ptr<ModelDataBatcher> modelDataBatcher;

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

struct ModelContext::ProviderKey
{
private:

	friend class CommandProvider;
	explicit ProviderKey() = default;
};






