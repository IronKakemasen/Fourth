#pragma once

class Model;

namespace ModelContextCmds
{
	using WatchModelContainer = std::function<const std::vector<std::unique_ptr<Model>>*()>;

}