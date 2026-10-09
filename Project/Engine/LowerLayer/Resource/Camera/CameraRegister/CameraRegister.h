#pragma once
#include "../CameraContextRuntime/CameraFrontlineSystems.h"


class CameraContext::CameraFrontlineSystems::CameraRegister
{
	friend class CameraContext::CameraFrontlineSystems;


	static CameraBehavior* Register
	(
		std::unique_ptr<CameraBehavior>&& camera_, 
		std::string const& name_,
		CameraLibrary& cameraLibrary_
	);
};

