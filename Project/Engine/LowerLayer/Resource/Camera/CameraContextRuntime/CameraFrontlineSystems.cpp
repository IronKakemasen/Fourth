#include "PreCompileHeader.h"
#include "CameraFrontlineSystems.h"
#include "../CameraLibrary/CameraLibrary.h"
#include "../CameraRegister/CameraRegister.h"
#include "../CameraStructrue/CameraBehavior.h"

CameraContext::CameraFrontlineSystems::CameraFrontlineSystems(NexusFieldProof proof_)
{
	cameraLibrary = std::make_unique<CameraLibrary>(proof_);

}

CameraContext::CameraFrontlineSystems::~CameraFrontlineSystems()
{

}

void CameraContext::CameraFrontlineSystems::RegisterCamera
(
	std::unique_ptr<CameraBehavior>&& camera_,
	CameraSocket dstCameraSocket_,
	std::string const& name_
)
{
	socketMap[dstCameraSocket_] = CameraRegister::Register(std::move(camera_), name_, *cameraLibrary);
}

void CameraContext::CameraFrontlineSystems::ChangeCamera(std::string const& to_, CameraSocket dstSocket_)
{
	socketMap[dstSocket_] = cameraLibrary->Export(to_);
}

void CameraContext::CameraFrontlineSystems::RunCameraUpdate()
{
	CameraBehavior::Local_UpdateLicence licenceUpdate;

	//更新する必要があるカメラ(描画のために使用しているカメラ)の更新処理を呼ぶ
	for (auto& [key, camera] : socketMap)
	{
		camera->Update(licenceUpdate);
		camera->UpdateMatrices(licenceUpdate);
	}
}

