#pragma once

class Model;
struct RenderStateKey;

namespace ModelContextCmds
{
	using WatchModelContainer = std::function<const std::vector<std::unique_ptr<Model>>*()>;
	using WatchSeparatedByRenderState = std::function<std::vector<std::unordered_map<uint64_t, std::pair<RenderStateKey, std::vector<Model*>>>>* ()>;
}