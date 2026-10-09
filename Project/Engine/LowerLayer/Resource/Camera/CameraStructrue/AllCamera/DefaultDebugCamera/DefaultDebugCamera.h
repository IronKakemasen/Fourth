#pragma once
#include "../CameraBehavior.h"

class DefaultDebugCamera :public CameraBehavior
{
public:

	DefaultDebugCamera(std::optional<CameraDesc> const& desc_);

	virtual void Update()override;

};

