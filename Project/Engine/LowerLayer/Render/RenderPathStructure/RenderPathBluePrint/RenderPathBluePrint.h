#pragma once
#include "../ShaderPathComponent.h"
#include "../RenderPathComponent.h"


///レンダーパスの設計図
namespace RenderPathBluePrint
{
	//テーブルから、使用するシェーダーの名前(キー)をShaderComponentをもとに定める
	struct ShaderTable;
	//テーブルから、使用するカラーバッファ、ディプスバッファを定める
	struct BufferTable;

};


