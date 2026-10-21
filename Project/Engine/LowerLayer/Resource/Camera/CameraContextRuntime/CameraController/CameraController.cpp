#include "PreCompileHeader.h"
#include "CameraController.h"
#include "../../CameraStructure/CameraBehavior.h"



CameraContext::CameraFrontlineSystems::CameraController::CameraController(NexusFieldProof proof_)
{

}

std::unordered_map<CameraSocket, CameraBehavior*> const& CameraContext::CameraFrontlineSystems::CameraController::Update()
{
	return RunCamera();
}

std::unordered_map<CameraSocket, CameraBehavior*> const& CameraContext::CameraFrontlineSystems::CameraController::RunCamera()
{
	CameraBehavior::Local_UpdateLicence licenceUpdate;

	//更新する必要があるカメラ(描画のために使用しているカメラ)の更新処理を呼ぶ
	for (auto& [key, camera] : socketMap)
	{
		camera->Update(licenceUpdate);
		camera->UpdateMatrices(licenceUpdate);
	}

	return socketMap;
}