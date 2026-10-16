#pragma once


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"

#include "../../../LowerLayer/Resource/Model/ModelContextRuntime/ModelFrontlineSystems/ModelFrontlineSystems.h"

class SceneContext;
class Model;
struct CameraDesc;

class SceneBehavior
{
	friend class SceneContext;

	//このシーンで使用しているカメラ、モデル、ライトなどの情報
	struct Output
	{
		//使用しているカメラ。更新必要
		std::unordered_map<CameraSocket, CameraBehavior*> usingCamera;

	};

public:

	SceneBehavior
	(
		CameraContext::CameraFrontlineSystems& cameraSystems_,
		ModelContext::ModelFrontlineSystems& modelSystems_
	);

	virtual ~SceneBehavior() = default;

	Output const& WatchSceneOutput()const;

protected:

	//カメラの作成＆登録
	template<CameraSocket dstSocket, typename CameraType>
	void CreateCamera
	(
		std::optional<CameraDesc> const& cameraDesc_,
		std::string const& name_
	)
	{
		cameraSystems.CreateCamera<dstSocket, CameraType>(cameraDesc_,name_);
	}

	//ゲームオブジェクトが好きなタイミングでカメラを切り替えられるように
	//カメラ切り替えコマンドを返す。
	template<CameraSocket dstSocket>
	CameraContext::CameraFrontlineSystems::CmdConnectCamera<dstSocket> GetCmdConnectCamera()
	{
		return cameraSystems.GetCmdConnectCamera<dstSocket>();
	}

private:

	//SceneContext::SceneControllerのみ呼べる
	void Update();
	void Reset();

	CameraContext::CameraFrontlineSystems& cameraSystems;
	ModelContext::ModelFrontlineSystems& modelSystems;

	SceneBehavior::Output output;

};

