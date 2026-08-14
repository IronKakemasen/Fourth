#pragma once
#include "../../ShaderPathComponent.h"
#include "../../RenderPassComponent.h"


///レンダーPassの設計図
namespace RenderPassBluePrint
{
	//使用するシェーダーの名前(キー)をShaderComponentをもとに定める
	struct ShaderTable;
	//使用するカラーバッファ、ディプスバッファの情報を定める
	struct BufferTable;
	//DepthEnable、DepthTestを定める
	struct RenderPassSettingTable;

};

