#pragma once

class Model;
struct RenderStateKey;
struct RenderState;

namespace ModelContextCmds
{
	using WatchAllModelsRenderStatePattern = std::function<std::vector<RenderState> const* ()>;
}