#pragma once
#include "../RenderPath.h"
#include "../RenderPassComponent.h"


struct RenderPath::Pass
{
	///そのパスで使用するバッファの情報をまとめたもの
	struct RequiredBufferInfo;

	Pass();
	~Pass();

	RenderPassState renderPassState;
	std::unique_ptr<RequiredBufferInfo> requiredBufferInfo;
};

