#pragma once

class SceneOpaque;
class SceneCompositor;
class GridlinePass;


using AllPassPtr = std::tuple
<
	SceneOpaque*, SceneCompositor*, GridlinePass*
>;

using AllPassTypes = std::tuple
<
	SceneOpaque, SceneCompositor, GridlinePass
>;