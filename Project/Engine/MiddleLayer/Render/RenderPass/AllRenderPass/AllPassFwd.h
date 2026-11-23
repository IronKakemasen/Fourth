#pragma once

class SceneOpaque;
class SceneCompositor;
class GridLinePass;


using AllPassPtr = std::tuple
<
	SceneOpaque*, SceneCompositor*, GridLinePass*
>;

using AllPassTypes = std::tuple
<
	SceneOpaque, SceneCompositor, GridLinePass
>;