#pragma once
#include "../ModelContext.h"
#include "../ModelContextCmds.h"
#include "RenderStateKey/RenderStateKey.h"
#include "../ModelStructure/Model.h"

class ModelContext::ModelContainer
{
	//1.モデルのレンダーステートごとにコンテナに詰めて、PSOの切り替えコストを低減させる
	//2.モデルをstaticかdynamicかでコンテナを仕分ける。バッチング処理の効率化のため
	class ModelSeparator;

public:

	using SeparatedByRenderState = std::unordered_map<uint64_t, std::pair<RenderStateKey , std::vector<Model*>>>;

	struct Local_AddLicence;

	ModelContainer(NexusFieldProof proof_);
	~ModelContainer();

	void Add(Local_AddLicence addLicence_,std::unique_ptr<Model>&& model_);

	//全モデルコンテナの中身を見るためのコマンド
	ModelContextCmds::WatchModelContainer WatchModelDataCmd(ProviderKey key_)const;
	//RenderStateで仕分けされたコンテナを見るためのコマンド
	ModelContextCmds::WatchSeparatedByRenderState WatchSeparatedByRenderStateCmd(ProviderKey key_);
	//モデルのタイプ別に仕分けされたコンテナを見るためのコマンド
	ModelContextCmds::WatchSeparatedByModelType WatchSeparatedByModelTypeCmd(ProviderKey key_);

	//ランタイムでPSO切り替えコストを低減させるために、モデルクラスをおなじrenderStateごとに分別する
	void SeparateModels(NexusFieldProof proof_, AgentKey key_);


private:

	//モデルがレンダーステートごとに分別されたコンテナ。
	//第一添え字は、Passで指定
	std::vector<SeparatedByRenderState> separatedByRenderState;

	//モデルの本体が詰まってる
	std::vector<std::unique_ptr<Model>> container;
	//staticかdynamicかで仕分けられている
	std::array < std::vector<Model*>, (UINT)Model::Type::kCount > separatedByModelType;
};

struct ModelContext::ModelContainer::Local_AddLicence
{
private:

	friend class ModelContext::ModelCreator;
	explicit Local_AddLicence() = default;
};



