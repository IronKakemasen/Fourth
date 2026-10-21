#pragma once
#include "../../CameraStructure/CameraBehavior.h"

class DefaultDebugCamera :public CameraBehavior
{
public:

	DefaultDebugCamera(std::optional<CameraDesc> const& desc_);

	virtual void Update(Local_UpdateLicence licence_)override;

};

