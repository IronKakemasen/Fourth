#include "PreCompileHeader.h"
#include "CameraBehavior.h"
#include "../CameraTransform/CameraTransform.h"
#include "../CameraDesc/CameraDesc.h"


CameraBehavior::CameraBehavior(std::optional<CameraDesc> const& desc_)
{
	trans = std::make_unique<CameraTransform>(desc_);
}


void CameraBehavior::UpdateMatrices(Local_UpdateMatricesLicence licence_)
{
	trans->UpdateMatrices(licence_);
}
