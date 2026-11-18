#pragma once



//外部
#include "../../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraFrontlineSystems.h"
#include "../../../GameObject/GameObjectRuntime/GameObjFrontSystems/GameObjFrontlineSystems.h"

class SceneRuntimeInterface
{
public:

	SceneRuntimeInterface
	(
		CameraContext::FrontlineSystems& cameraSystems_,
		GameObjectContext::FrontlineSystems& gameObjSystems_
	): cameraSystems(cameraSystems_), gameObjSystems(gameObjSystems_)
	{

	}

	//カメラ切り替えコマンドを返す
	//ゲームオブジェクトが好きなタイミングでカメラを切り替えられるように
	template<CameraSocket dstSocket>
	[[nodiscard]] CameraContext::FrontlineSystems::CmdConnectCamera<dstSocket> GetCmdConnectCamera()
	{
		return cameraSystems.GetCmdConnectCamera<dstSocket>();
	}

	//オブジェを名前から検索する
	//単一バージョン
	[[nodiscard]] GameObjectBehavior* FindAnObject(std::string const& objName_)
	{
		return gameObjSystems.FindObjects(objName_)[0];
	}
	//複数バージョン
	[[nodiscard]] std::vector<GameObjectBehavior*>& FindObjects(std::string const& objName_)
	{
		return gameObjSystems.FindObjects(objName_);
	}



private:

	CameraContext::FrontlineSystems& cameraSystems;
	GameObjectContext::FrontlineSystems& gameObjSystems;
};

