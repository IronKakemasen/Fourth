#pragma once

class Nexus;
class BufferContextDiplomat;
class ModelContextDiplomat;
class TextureContextDiplomat;


class ModelContext
{
	//モデルファイルからモデル情報を読み込む
	class ModelDataLoader;
	//TransformMatrixSlotの空きインデックスを割り当てたり、モデル名をもとに
	//モデルデータの割り当てを行う
	class ModelSlotAllocator;
	//モデルデータの一時キャッシュ
	class ModelDataCache;
	//モデルファイルから読み込んだデータ
	struct ModelDataFromFile;
	//モデルが実際に所持するデータ
	struct ModelData;
	//全てのモデルファイルのモデルデータのバッファを生成する。
	class ModelDataCreator;
	///モデルクラスを生成する
	class ModelCreator;
	//モデルの書き込まなくてはならないデータ(TransformMatrixなど)のバッチングを行う
	class ModelDataBatcher;

public:
	//シーンが1つ所持するモデルのシステム群
	class ModelFrontlineSystems;
	//ModelFrontlineSystemsをシーンにディスパッチする
	class ModelFSDispatcher;


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


	ModelContext
	(
		NexusFieldProof proof_, 
		BufferContextDiplomat& bufferContextDiplomat_,
		TextureContextDiplomat& textureContextDiplomat_
	);
	~ModelContext();

	///代役に、モデルデータのキャッシュを消してもらう
	void DeleteModelDataCache(NexusFieldProof proof_, AgentKey agentKey_);
	auto& AccessDiplomat() { return *diplomat; }


private:


	std::unique_ptr<ModelSlotAllocator> modelSlotAllocator;
	std::unique_ptr<ModelCreator> modelCreator;
	std::unique_ptr<ModelDataBatcher> modelDataBatcher;
	std::unique_ptr<ModelDataCache> modelDataCache;
	std::unique_ptr<ModelFSDispatcher> modelFSDispatcher;

	//外交官
	std::unique_ptr<ModelContextDiplomat> diplomat;
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






