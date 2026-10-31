#pragma once



//外部
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"


class SceneRuntimeInterface
{
public:

	SceneRuntimeInterface
	(
		CameraContext::FrontlineSystems* cameraSystems_
	): cameraSystems(cameraSystems_)
	{

	}

	//カメラ切り替えコマンドを返す
	//ゲームオブジェクトが好きなタイミングでカメラを切り替えられるように
	template<CameraSocket dstSocket>
	[[nodiscard]] CameraContext::FrontlineSystems::CmdConnectCamera<dstSocket> GetCmdConnectCamera()
	{
		return cameraSystems->GetCmdConnectCamera<dstSocket>();
	}


private:

	CameraContext::FrontlineSystems* cameraSystems;
};

