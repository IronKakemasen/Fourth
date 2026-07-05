#pragma once
#include "../RenderPathComposer.h"
#include "../../ShaderPathComponent.h"

struct RenderPath::PathComposer::ShaderCombiner
{
	RenderPath::MS_PS Combine(ShaderLibrary* lib_, std::string const msKey_, std::string const psKey_);

};

