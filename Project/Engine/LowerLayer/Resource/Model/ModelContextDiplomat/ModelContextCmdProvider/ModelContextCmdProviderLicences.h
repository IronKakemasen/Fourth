#pragma once
#include "ModelContextCmdProvider.h"

class RenderContext;

struct ModelContext::CommandProvider::WatchModelContainerLicence
{
private:

	friend class RenderContext;
	explicit WatchModelContainerLicence() = default;
};

