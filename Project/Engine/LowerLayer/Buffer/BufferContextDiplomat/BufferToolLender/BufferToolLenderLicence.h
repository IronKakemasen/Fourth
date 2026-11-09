#pragma once
#include "BufferToolLender.h"

class ModelContext;
class RenderContext;
class TextureContext;
class CameraContext;
class MaterialContext;


struct BufferContext::ToolLender::BasicBufferManagementLicence
{
private:

	friend class ModelContext;
	friend class RenderContext;
	friend class TextureContext;
	friend class CameraContext;
	friend class MaterialContext;

	explicit BasicBufferManagementLicence() = default;
};

struct BufferContext::ToolLender::UsesGlobalConstantBuffersLicence
{
private:

	friend class RenderContext;

	explicit UsesGlobalConstantBuffersLicence() = default;
};



