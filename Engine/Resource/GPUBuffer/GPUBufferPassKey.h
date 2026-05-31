#pragma once
#include "GPUBufferBehavior.h"


class GPUBufferCreator;
class GpuBufferManager;

struct GPUBufferBehavior::CreateKey
{
private:

	friend class GPUBufferCreator;

	explicit CreateKey() = default;
};

struct GPUBufferBehavior::BufferAccessKey
{
private:
	friend class GPUBufferCreator;
	friend class GpuBufferManager;

	explicit BufferAccessKey() = default;
};
