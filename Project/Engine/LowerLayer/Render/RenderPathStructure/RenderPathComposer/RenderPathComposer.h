#pragma once
#include "../RenderPath.h"

class ShaderLibrary;

class RenderPath::PathComposer
{
	PathComposer(RenderContext::NexusFieldProof proof_, ShaderLibrary* shaderLibrary_);


public:

	//使用するシェーダーのセットをShaderPathComponentから組み合わせる
	struct ShaderCombiner;


};

