#include "PreCompileHeader.h"
#include "DefaultDebugCamera.h"
#include "../../CameraStructrue/CameraTransform/CameraTransform.h"
#include "../../CameraStructrue/CameraDesc/CameraDesc.h"


DefaultDebugCamera::DefaultDebugCamera(std::optional<CameraDesc> const& desc_)
	: CameraBehavior(desc_)
{

}

void DefaultDebugCamera::Update(Local_UpdateLicence licence_)
{

}
