#pragma once
#include "AllSceneInterfaceFwd.h"

//外部
#include "../../GameObject/GameObjectRuntime/GameObjFrontSystems/GameObjFrontlineSystems.h"

#include "../../../LowerLayer/Resource/Camera/CameraContext.h"

#include "../../../LowerLayer/Resource/Model/ModelContext.h"

#include "../../../LowerLayer/Resource/Material/MaterialContext.h"

class SceneContext;
class Model;
struct CameraDesc;

class SceneBehavior
{
	//おおざっぱだが必要な情報のみ開示したいのでフレンド登録
	friend class SceneContext;

	//シーンのコンフィグ
	struct SceneConfig;

public:

	//このシーンで使用しているカメラ、モデル、ライトなどの情報
	struct Output;

	//そこいらでインスタンス化させないため
	struct InstancingLicense;

	SceneBehavior(InstancingLicense license_);
	virtual ~SceneBehavior();

		
protected:

	template<typename ObjType>
	ObjType* CreateObj(std::string const& name_)
	{
		return objSystems->CreateObj<ObjType>(name_);
	}

private:

	//ここの中でゲームオブジェクトの生成などの処理を書く。シーンが切り替わっても一発しか呼びません。
	virtual void Init() = 0;

	//シーンのInit()の後に一括で一度だけ呼ばれる
	void SeparateModels();

	//シーンクリエイターがインスタンス化後に呼び出す
	void SetSystems
	(
		CameraContext::FrontlineSystems* cameraSystems_,
		ModelContext::FrontlineSystems* modelSystems_,
		GameObjectContext::FrontlineSystems* objFrontlineSystems_,
		MaterialContext::FrontlineSystems* materialSystems_
	);

	//ゲームオブジェクトの初期化。その後、ゲームオブジェクトのInitInterfaceを削除する
	void InitAllGameObj(std::string const& sceneName_);

	//シーンクリエイターがプリセットカメラを備え付ける
	void CreatePresetCamera();

	//jsonファイルから設定を読み込み書き込まれたデータを取り込む
	void SetSceneConfig(std::unique_ptr<SceneConfig>&& sceneConfig_);

	//SceneContext::SceneControllerのみ呼べる
	void Update();

	//SceneControllerにこのシーンで使われているリソース伝えるため
	Output const& WatchSceneOutput()const;

	//ゲームオブジェクトの初期化専用インターフェースを削除する
	void DeleteInitInterface();

	//他コンテキストのシステム
	CameraContext::FrontlineSystems* cameraSystems = nullptr;
	ModelContext::FrontlineSystems* modelSystems = nullptr;
	GameObjectContext::FrontlineSystems* objSystems = nullptr;
	MaterialContext::FrontlineSystems* materialSystems = nullptr;

	//シーンの出力物
	std::unique_ptr<Output> output;
	//シーンの設定
	std::unique_ptr<SceneConfig> sceneConfig;

	//シーンのインターフェース群
	SceneInterfacesUnique interfaces;
};


struct SceneBehavior::InstancingLicense
{

private:
	friend class SceneContext;
	explicit InstancingLicense() = default;
};
