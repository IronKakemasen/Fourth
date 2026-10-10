#include "PreCompileHeader.h"
#include "CameraFrontlineSystems.h"
#include "CameraLibrary/CameraLibrary.h"
#include "CameraController/CameraController.h"

CameraContext::CameraFrontlineSystems::CameraFrontlineSystems(NexusFieldProof proof_)
{
	cameraLibrary = std::make_unique<CameraLibrary>(proof_);
	cameraController = std::make_unique<CameraController>(proof_);
}

CameraContext::CameraFrontlineSystems::~CameraFrontlineSystems()
{

}

void CameraContext::CameraFrontlineSystems::ImportCamera(std::unique_ptr<CameraBehavior>&& camera_, std::string const& name_)
{
	cameraLibrary->Import(std::move(camera_), name_);
}


void CameraContext::CameraFrontlineSystems::RunCameraUpdate()
{
	cameraController->RunCamera();
}

template<>
void CameraContext::CameraFrontlineSystems::Connect<CameraSocket::kMainDebug>(std::string const& name_)
{
	cameraController->Connect<CameraSocket::kMainDebug>(cameraLibrary->Export(name_));
}



template
void CameraContext::CameraFrontlineSystems::Connect<CameraSocket::kMainDebug>(std::string const& name_);
