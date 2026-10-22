#pragma once


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"

#include "../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"

class SceneContext;
class Model;
struct CameraDesc;

class SceneBehavior
{
	//おおざっぱだが必要な情報のみ開示したいのでフレンド登録
	friend class SceneContext;

	//このシーンで使用しているカメラ、モデル、ライトなどの情報
	struct Output
	{
		//使用しているカメラ。更新必要
		std::unordered_map<CameraSocket, CameraBehavior*> usingCamera;
		//このシーンのモデルコンテナ
		ModelContext::ModelFrontlineSystems::ModelContainer const* modelContainer = nullptr;
		//staticなモデルを毎回バッチング処理しないようにするため
		UINT leftStaticModelBatchingCnt = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;
	};

protected:

	//そこいらでインスタンス化させないため
	struct InstancingLicense;

	//カメラの作成＆登録
	template<CameraSocket dstSocket, typename CameraType>
	[[nodiscard]] CameraType* CreateCamera
	(
		std::optional<CameraDesc> const& cameraDesc_,
		std::string const& name_
	)
	{
		return cameraSystems->CreateCamera<dstSocket, CameraType>(cameraDesc_,name_);
	}

	//ゲームオブジェクトが好きなタイミングでカメラを切り替えられるように
	//カメラ切り替えコマンドを返す。
	template<CameraSocket dstSocket>
	[[nodiscard]] CameraContext::CameraFrontlineSystems::CmdConnectCamera<dstSocket> GetCmdConnectCamera()
	{
		return cameraSystems->GetCmdConnectCamera<dstSocket>();
	}

	//モデル作成し、そのポインタを返す
	template<Model::Type modelType>
	[[nodiscard]] std::vector<Model*> CreateModel
	(
		std::string const& modelFileName_,
		std::vector<RenderState> const& modelRenderStates_,
		std::vector<StructuredBufferModelData::MaterialCPU> const& materials_,
		UINT const numCreate_,
		std::string const& modelName_ = "nameLess"
	)
	{
		return modelSystems->CreateModel<modelType>
		(
			modelFileName_,
			modelRenderStates_,
			materials_,
			numCreate_,
			modelName_
		);			
	}

public:

	SceneBehavior(InstancingLicense const& license_) {};
	virtual ~SceneBehavior() = default;

private:


	//ここの中でモデルの生成などの処理を書く。シーンが切り替わっても一発しか呼びません。
	virtual void Init() = 0;

	//シーンのInit()の後に一括で一度だけ呼ばれる
	void SeparateModels();

	//シーンクリエイターがインスタンス化後に呼び出す
	void SetSystems
	(
		CameraContext::CameraFrontlineSystems* cameraSystems_,
		ModelContext::ModelFrontlineSystems* modelSystems_
	);

	//シーンクリエイターがプリセットカメラを備え付ける
	void CreatePresetCamera();

	//SceneContext::SceneControllerのみ呼べる
	void Update();

	//SceneControllerにこのシーンで使われているリソース伝えるため
	Output const& WatchSceneOutput()const;

	//他コンテキストのシステム
	CameraContext::CameraFrontlineSystems* cameraSystems = nullptr;
	ModelContext::ModelFrontlineSystems* modelSystems = nullptr;
	

	//シーンの出力物
	SceneBehavior::Output output;


};


struct SceneBehavior::InstancingLicense
{

private:
	friend class SceneContext;
	explicit InstancingLicense() = default;
};
