#include "PreCompileHeader.h"
#include "CameraRegister.h"
#include "../CameraLibrary/CameraLibrary.h"

CameraBehavior* CameraContext::CameraFrontlineSystems::CameraRegister::Register
(
	std::unique_ptr<CameraBehavior>&& camera_,
	std::string const& name_,
	CameraLibrary& cameraLibrary_
)
{
	auto* cameraPtr = camera_.get();
	cameraLibrary_.Import(std::move(camera_), name_);

	return cameraPtr;
}

