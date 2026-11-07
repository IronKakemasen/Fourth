#pragma once
#include "BufferContextCmdProvider.h"

class ModelContext;
class TextureContext;
class RenderContext;
class CameraContext;
class ShaderContext;


struct BufferContext::CmdProvider::UsesCBufferCreatorLicence
{
private:

	friend class ModelContext;
	friend class TextureContext;
	friend class RenderContext;
	friend class CameraContext;
	friend class ShaderContext;


	explicit UsesCBufferCreatorLicence() = default;
};


