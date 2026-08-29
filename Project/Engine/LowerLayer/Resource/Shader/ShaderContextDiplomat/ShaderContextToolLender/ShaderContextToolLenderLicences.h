#pragma once
#include "ShaderContextToolLender.h"
#include "../../../../Render/RenderContext.h"


struct ShaderContext::ToolLender::UsesShaderLibraryLicence
{
private:

	friend class RenderContext::RenderGraph;
	explicit UsesShaderLibraryLicence() = default;

};

