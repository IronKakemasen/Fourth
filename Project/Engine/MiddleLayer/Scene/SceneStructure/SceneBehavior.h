#pragma once


//外部
#include "../../../LowerLayer/Resource/Camera/CameraContext.h"
#include "../../../LowerLayer/Resource/Camera/CameraContextRuntime/CameraSocket.h"

class CameraBehavior;

class SceneBehavior
{
	struct Output
	{
		//使用しているカメラ
		std::unordered_map<CameraSocket, CameraBehavior*> usiggCamera;
	};

public:

	Output Update();

	SceneBehavior
	(
		CameraContext::CameraFrontlineSystems& cameraSystems_
	);

private:

	CameraContext::CameraFrontlineSystems& cameraSystems;
};

