#pragma once

class SceneTextureCreatorOpaque;
class SceneTextureCompositor;

using AllPassPtr = std::tuple<SceneTextureCreatorOpaque*, SceneTextureCompositor*>;
using AllPassTypes = std::tuple<SceneTextureCreatorOpaque, SceneTextureCompositor>;