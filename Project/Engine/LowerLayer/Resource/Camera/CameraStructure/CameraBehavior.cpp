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


StructuredBufferCameraData::CameraDataCPUGPU CameraBehavior::OutCameraData()const
{
	auto const& base = trans->WatchBase();
	auto const& matrices = trans->WatchMatrices();
	auto const worldPos = trans->WatchWorldPosition();

	return StructuredBufferCameraData::CameraDataCPUGPU
	{
		matrices.view,
		matrices.proj,
		matrices.viewProj,
		Vector4<float>{worldPos.data.x,worldPos.data.y,worldPos.data.z,1.0f},
		Vector4<float>{base.lookDir.data.x,base.lookDir.data.y,base.lookDir.data.z,0.0f}
	};

}

