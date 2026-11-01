#pragma once
#include "AllSceneInterfaceFwd.h"

//外部
#include "../../GameObject/GameObjectRuntime/GameObjFrontSystems/GameObjFrontlineSystems.h"

#include "../../../LowerLayer/Resource/Camera/CameraContext.h"

#include "../../../LowerLayer/Resource/Model/ModelContext.h"

class SceneContext;
class Model;
struct CameraDesc;

class SceneBehavior
{
	//おおざっぱだが必要な情報のみ開示したいのでフレンド登録
	friend class SceneContext;

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
		return objFrontlineSystems->CreateObj<ObjType>(name_);
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
		GameObjectContext::FrontlineSystems* objFrontlineSystems_
	);

	//ゲームオブジェクトの初期化
	void InitAllGameObj(std::string const& sceneName_);

	//シーンクリエイターがプリセットカメラを備え付ける
	void CreatePresetCamera();

	//SceneContext::SceneControllerのみ呼べる
	void Update();

	//SceneControllerにこのシーンで使われているリソース伝えるため
	Output const& WatchSceneOutput()const;

	//ゲームオブジェクトの初期化専用インターフェースを削除する
	void DeleteInitInterface();

	//他コンテキストのシステム
	CameraContext::FrontlineSystems* cameraSystems = nullptr;
	ModelContext::FrontlineSystems* modelSystems = nullptr;
	GameObjectContext::FrontlineSystems* objFrontlineSystems = nullptr;

	//シーンの出力物
	std::unique_ptr<Output> output;

	//シーンのインターフェース群
	SceneInterfacesUnique interfaces;
};


struct SceneBehavior::InstancingLicense
{

private:
	friend class SceneContext;
	explicit InstancingLicense() = default;
};
