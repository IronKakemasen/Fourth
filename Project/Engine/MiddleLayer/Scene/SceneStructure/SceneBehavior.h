#pragma once


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"


class SceneContext;

class SceneBehavior
{
	friend class SceneContext;

	struct Output
	{
		//使用しているカメラ
		std::unordered_map<CameraSocket, CameraBehavior*> usingCamera;
	};

public:

	SceneBehavior
	(
		CameraContext::CameraFrontlineSystems* cameraSystems_
	);

	virtual ~SceneBehavior() = default;

protected:

	//カメラの作成＆登録
	template<CameraSocket dstSocket, typename CameraType>
	void CreateCamera
	(
		std::optional<CameraDesc> const& cameraDesc_,
		std::string const& name_
	)
	{
		cameraSystems->CreateCamera<dstSocket, CameraType>(cameraDesc_,name_);
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
	Output Update();
	void Reset();

	CameraContext::CameraFrontlineSystems* cameraSystems;
};

