#pragma once

class SceneOpaque;
class SceneCompositor;

using AllPassPtr = std::tuple<SceneOpaque*, SceneCompositor*>;
using AllPassTypes = std::tuple<SceneOpaque, SceneCompositor>;