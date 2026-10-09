#include "PreCompileHeader.h"
#include "DefaultDebugCamera.h"
#include "../../CameraTransform/CameraTransform.h"
#include "../../CameraDesc/CameraDesc.h"


DefaultDebugCamera::DefaultDebugCamera(std::optional<CameraDesc> const& desc_)
	: CameraBehavior(desc_)
{

}

void DefaultDebugCamera::Update()
{

}
