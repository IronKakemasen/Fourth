#include "PreCompileHeader.h"
#include "CameraController.h"
#include "../../CameraStructrue/CameraBehavior.h"



CameraContext::CameraFrontlineSystems::CameraController::CameraController(NexusFieldProof proof_)
{

}

void CameraContext::CameraFrontlineSystems::CameraController::Update()
{
	RunCamera();
}

void CameraContext::CameraFrontlineSystems::CameraController::RunCamera()
{
	CameraBehavior::Local_UpdateLicence licenceUpdate;

	//更新する必要があるカメラ(描画のために使用しているカメラ)の更新処理を呼ぶ
	for (auto& [key, camera] : socketMap)
	{
		camera->Update(licenceUpdate);
		camera->UpdateMatrices(licenceUpdate);
	}

}