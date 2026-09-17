#pragma once
#include "TextureContextToolLender.h"

class ModelContext;


struct TextureContext::ToolLender::UsesTextureLibLicence
{
private:

	friend class ModelContext;
	explicit UsesTextureLibLicence() = default;
};