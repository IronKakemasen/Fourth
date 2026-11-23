#pragma once
#include "SceneOpaque/SceneOpaque.h"
#include "SceneCompositor/SceneCompositor.h"
#include "Gridline/GridLinePass.h"


using AllPassUnique = std::tuple
<
	std::unique_ptr<SceneOpaque>,
	std::unique_ptr<SceneCompositor>,
	std::unique_ptr<GridLinePass>
	
>;
