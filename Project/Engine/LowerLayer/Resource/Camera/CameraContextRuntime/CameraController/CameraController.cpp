#include "PreCompileHeader.h"
#include "CameraController.h"
#include "../../CameraStructure/CameraBehavior.h"



CameraContext::FrontlineSystems::CameraController::CameraController(NexusFieldProof proof_)
{

}

std::unordered_map<CameraSocket, CameraBehavior*> const& CameraContext::FrontlineSystems::CameraController::Update()
{
	return RunCamera();
}

std::unordered_map<CameraSocket, CameraBehavior*> const& CameraContext::FrontlineSystems::CameraController::RunCamera()
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