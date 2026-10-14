#pragma once
#include "../ModelFrontlineSystems.h"
#include "../RenderStateKey.h"
#include "../../../ModelContextCmds.h"
#include "../../../ModelStructure/Model.h"

class ModelContext::ModelFrontlineSystems::ModelContainer
{
	//1.モデルのレンダーステートごとにコンテナに詰めて、PSOの切り替えコストを低減させる
	//2.モデルをstaticかdynamicかでコンテナを仕分ける。バッチング処理の効率化のため
	class ModelSeparator;

public:

	using SeparatedByRenderState = std::unordered_map<uint64_t, std::pair<RenderStateKey , std::vector<Model*>>>;

	struct Local_InitLicence;

	ModelContainer(NexusFieldProof proof_);
	~ModelContainer();


	//モデルのタイプ別に仕分けされたコンテナを見るため
	auto const& WatchSeparatedByModelType()const { return separatedByModelType; }
	//レンダーステート別
	auto const& WatchSeparatedByRenderState()const { return separatedByRenderState; }

	//modelCreatorが作成したモデル本体を格納
	void Add(Local_InitLicence licence_, std::unique_ptr<Model>&& model_);

	//ランタイムでPSO切り替えコストを低減させるために、モデルクラスをおなじrenderStateごとに分別する
	void SeparateModels(Local_InitLicence licence_);


private:

	//モデルの本体が詰まってる
	std::vector<std::unique_ptr<Model>> container;

	//モデルがレンダーステートごとに分別されたコンテナ。
	//第一添え字は、Passで指定
	std::vector<SeparatedByRenderState> separatedByRenderState;

	//staticかdynamicかで仕分けられている
	std::array < std::vector<Model*>, (UINT)Model::Type::kCount > separatedByModelType;
};

struct ModelContext::ModelFrontlineSystems::ModelContainer::Local_InitLicence
{
private:

	friend class ModelContext::ModelFrontlineSystems;
	explicit Local_InitLicence() = default;
};



