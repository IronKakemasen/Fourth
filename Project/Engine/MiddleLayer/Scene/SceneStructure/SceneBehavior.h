#pragma once


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"

#include "../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"

class SceneContext;
class Model;
struct CameraDesc;
class SceneInitInterface;
class SceneRuntimeInterface;

class SceneBehavior
{
	//おおざっぱだが必要な情報のみ開示したいのでフレンド登録
	friend class SceneContext;

public:

	//そこいらでインスタンス化させないため
	struct InstancingLicense;

	SceneBehavior(InstancingLicense license_);
	virtual ~SceneBehavior();

	//このシーンで使用しているカメラ、モデル、ライトなどの情報
	struct Output;

protected:


private:


	//ここの中でモデルの生成などの処理を書く。シーンが切り替わっても一発しか呼びません。
	virtual void Init() = 0;

	//シーンのInit()の後に一括で一度だけ呼ばれる
	void SeparateModels();

	//シーンクリエイターがインスタンス化後に呼び出す
	void SetSystems
	(
		CameraContext::FrontlineSystems* cameraSystems_,
		ModelContext::FrontlineSystems* modelSystems_
	);

	//シーンクリエイターがプリセットカメラを備え付ける
	void CreatePresetCamera();

	//SceneContext::SceneControllerのみ呼べる
	void Update();

	//SceneControllerにこのシーンで使われているリソース伝えるため
	Output const& WatchSceneOutput()const;

	//他コンテキストのシステム
	CameraContext::FrontlineSystems* cameraSystems = nullptr;
	ModelContext::FrontlineSystems* modelSystems = nullptr;
	

	//シーンの出力物
	std::unique_ptr<Output> output;

	//シーンのインターフェース群
	std::tuple
	<
		std::unique_ptr<SceneInitInterface>,		//シーン初期化用のインターフェース。初期化フェーズが終わったら破棄
		std::unique_ptr<SceneRuntimeInterface>		//シーンのランタイム用インターフェース。破棄されない
	> interfaces;

};


struct SceneBehavior::InstancingLicense
{

private:
	friend class SceneContext;
	explicit InstancingLicense() = default;
};
