#pragma once
#include "RenderPassComponent.h"
#include "../RenderContext.h"

class RenderContext::PassBehavior
{
public:
	PassBehavior();
	virtual ~PassBehavior() = default;

	///そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo;
	struct PassSettings;

	std::unique_ptr<PassSettings> passSettings;
	std::unique_ptr<RequiredBufferInfo> requiredBufferInfo;
};

