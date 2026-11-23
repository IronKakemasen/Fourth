#include "PreCompileHeader.h"
#include "DefaultDebugCamera.h"
#include "../../CameraStructure/CameraTransform/CameraTransform.h"
#include "../../CameraStructure/CameraDesc/CameraDesc.h"


DefaultDebugCamera::DefaultDebugCamera(std::optional<CameraDesc> const& desc_)
	: CameraBehavior(desc_)
{
	trans->TranslatePosition({ 0,5,-3 });
	trans->LookAt({ 0.0f,-0.75f,1.0f });
}

void DefaultDebugCamera::Update(Local_UpdateLicence licence_)
{

}
