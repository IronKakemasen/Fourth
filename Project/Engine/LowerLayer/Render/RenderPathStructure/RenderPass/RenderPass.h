#pragma once
#include "../RenderPath.h"
#include "../RenderPassComponent.h"


struct RenderPath::Pass
{
	Pass();
	~Pass();

	///そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo;
	struct PassSettings;

	std::unique_ptr<PassSettings> passSettings;
	std::unique_ptr<RequiredBufferInfo> requiredBufferInfo;
};

