#pragma once
#include "ModelContextCmdProvider.h"
#include "../../../../Render/RenderContext.h"

struct ModelContext::CommandProvider::WatchModelContainerLicence
{
private:

	friend class RenderContext::RenderGraph;
	explicit WatchModelContainerLicence() = default;
};

