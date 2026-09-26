#pragma once
#include "../ModelContext.h"
#include "../ModelContextCmds.h"
#include "RenderStateKey/RenderStateKey.h"


class ModelContext::ModelContainer
{
	//モデルのレンダーステートごとにコンテナに詰めて、PSOの切り替えコストを低減させるため
	class ModelSeparator;

public:

	using SepartatedContainer = std::unordered_map<uint32_t, std::pair<RenderStateKey , std::vector<Model*>>>;

	struct Local_AddLicence;

	ModelContainer(NexusFieldProof proof_);
	~ModelContainer();

	void Add(Local_AddLicence addLicence_,std::unique_ptr<Model>&& model_);

	//全モデルコンテナの中身を見るためのコマンド
	ModelContextCmds::WatchModelContainer WatchDataCmd(ProviderKey key_)const;

	//ランタイムでPSO切り替えコストを低減させるために、モデルクラスをおなじrenderStateごとに分別する
	void SeparateModels(NexusFieldProof proof_, AgentKey key_);

private:

	//モデルがレンダーステートごとに分別されたコンテナ。
	//第一添え字は、Passで指定
	std::vector<SepartatedContainer> separatedContainer;

	//モデルの本体が詰まってる
	std::vector<std::unique_ptr<Model>> container;

};

struct ModelContext::ModelContainer::Local_AddLicence
{
private:

	friend class ModelContext::ModelCreator;
	explicit Local_AddLicence() = default;
};



