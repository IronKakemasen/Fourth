#pragma once
#include "../../CreateModelTools/ModelCreator.h"

struct RenderStateKey;


class ModelContext::FrontlineSystems
{
public:

	//モデルのコンテナ。シーン1つにつき1こ。モデルの本体、renderState別と、
	//modelType別に分類されたコンテナも持つ
	class ModelContainer;

	FrontlineSystems(NexusFieldProof proof_, ModelCreator& modelCreator_);
	~FrontlineSystems();

	//モデル作成し、そのポインタを返す
	template<Model::MeshUpdateType type>
	std::vector<Model*> CreateModel
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		UINT const numCreate_,
		std::string const& modelName_
	)
	{
		return AddModel<type>
		(
			modelCreator.Create<type>
			(
				modelFileName_,
				modelRenderStates_,
				numCreate_,
				modelName_
			)
		);
	}

	//モデルファイルからMaterialStandardを入力する
	void InputMaterialStandard(std::string const& modelFileName_, Model& model_);


	//モデルのトランスフォームのアップデート
	template<Model::MeshUpdateType modelType>
	void UpdateModelTransform();

	//モデルのトランスフォームの更新フラグをリセットする
	template<Model::MeshUpdateType modelType>
	void ResetModelTransformFrameFlag();


	//モデルコンテナの分別を行う
	void SeparateModels();

	ModelContainer const* WatchModelContainer()const;

private:

	template<Model::MeshUpdateType modelType>
	std::vector<Model*> AddModel(std::vector<std::unique_ptr<Model>>&& modelUniques_);

	std::unique_ptr<ModelContainer> modelContainer;
	ModelCreator& modelCreator;

};
