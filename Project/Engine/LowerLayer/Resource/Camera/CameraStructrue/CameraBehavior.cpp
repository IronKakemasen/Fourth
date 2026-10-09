#include "PreCompileHeader.h"
#include "CameraBehavior.h"
#include "CameraTransform/CameraTransform.h"
#include "CameraDesc/CameraDesc.h"


CameraBehavior::CameraBehavior(std::optional<CameraDesc> const& desc_)
{
	trans = std::make_unique<CameraTransform>(desc_);
}


void CameraBehavior::UpdateMatrices(Local_UpdateLicence licence_)
{
	trans->UpdateMatrices(licence_);
}

void CameraBehavior::Clear()
{
	trans->Clear();
}

void CameraBehavior::BeChild(Transform* parent_)
{
	trans->BeChild(parent_);
}

void CameraBehavior::Follow(Transform* followTarget_)
{
	trans->Follow(followTarget_);
}

CameraBehavior::Matrices const& CameraBehavior::WatchMatrices()const
{
	return trans->WatchMatrices();
}

